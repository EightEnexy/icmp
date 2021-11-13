#include <iostream>
#include <regex>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>


#include "server.h"
#include "prog_parse.h"
#include "client.h"

#define IP_HOSTNAME "-s"
#define FILE "-r"
#define SERVER 2




enum err {arg=1,cl};

void err_msg(const int err_code){
	
	switch(err_code){
		case arg:
			std::cerr << "unsupported option" << std::endl;
			std::cerr << "Usage:" << std::endl;	
			std::cerr << "secret -r <file> -s <ip|hostname> [-l]" << std::endl;
			exit(err_code);
		case cl:
			std::cerr << "client err" << std::endl;
			exit(err_code);

	}
}


int main(int argc,char*argv[]){

	using namespace std;
	
	prog prog({"r:s:","l"});

	if (!prog.parse(argc,argv))
		err_msg(arg);
	
	if (argc == SERVER){

		server icmp(socket(AF_INET,SOCK_RAW,IPPROTO_ICMP),socket(AF_INET,SOCK_RAW,IPPROTO_ICMPV6));

		char recv[MAX_LENGHT];
	
		memset(recv, 0, MAX_LENGHT);

		icmp.set_file_name(recv,MAX_LENGHT);

		ofstream icmp_file("M"+icmp.get_file_name(),ifstream::binary);

		size_t file_lenght = icmp.get_file_lenght();

		icmp.set_decrypt_key();
		
		while(file_lenght){

			int file_packet = icmp.read_packet(recv,(file_lenght > MAX_LENGHT-OFFSET)? MAX_LENGHT : file_lenght + OFFSET);
			file_packet -= ICMPHDR;
			file_packet -= (AES_BLOCK_SIZE-(((file_lenght > MAX_LENGHT-OFFSET)? MAX_LENGHT - OFFSET : file_lenght)%AES_BLOCK_SIZE));
    		file_lenght -= file_packet;

    		
			icmp.decrypt_data(file_packet,recv+ICMPHDR);
			icmp_file.write(recv+ICMPHDR,file_packet);
			
		}
		
		icmp_file.close();
			
	}
	else{
		
		client icmp(prog.get_arg_by_key(IP_HOSTNAME),prog.get_arg_by_key(FILE),AF_UNSPEC,SOCK_RAW);
		
		if (!icmp.get_info())
			err_msg(cl);
		
		icmp.get_ip();
		int sock;

		if((sock = icmp.get_sock()) == -1)
			err_msg(cl);
		
		
		ifstream icmp_file(icmp.get_file(),	ifstream::binary);

		if(not icmp_file)
				err_msg(cl);

		icmp_file.seekg (0, icmp_file.end);
    	size_t file_length = icmp_file.tellg();
    	icmp_file.seekg (0, icmp_file.beg);

    	char buffer[MAX_LENGHT];

    	icmp.set_encrypt_key();

    	icmp.send_file_data(sock,file_length,buffer);    	
    	
		
		//cout<<buffer;
	
    	/*
    	char OK[1500];
    	memset(OK, 0, 1500);
    	
    	struct sockaddr_in  addr;
		socklen_t addr_len = sizeof(struct sockaddr_in);

    	int sock2 = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
    	*/

   		while(file_length){

   			memset(buffer, 0, MAX_LENGHT);

			int file_packet = (file_length > MAX_LENGHT-OFFSET)? MAX_LENGHT - OFFSET : file_length;

    		file_length -= file_packet;

    		icmp_file.read(buffer + sizeof(icmphdr),file_packet);
    		icmp.encrypt_data(file_packet,buffer + sizeof(icmphdr));
			((struct icmphdr *)buffer)->code = ICMP_ECHO;
			
			icmp.send(sock,buffer,file_packet+sizeof(icmphdr)+(AES_BLOCK_SIZE-(file_packet%AES_BLOCK_SIZE)));
			
				
			}
			

			/*
			recvfrom(socket(AF_INET,SOCK_RAW,IPPROTO_ICMP),OK, sizeof(OK), 0,(sockaddr *)&addr, &addr_len);
			
			string server_msg;

			if(!(OK[28]=='O' && OK[29]=='K'))
				err_msg(cl);

			memset(OK, 0, 31);
			*/			
			

		
    	
    	icmp.free_addr();
	}

	
			
}