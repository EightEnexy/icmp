#include <iostream>
#include <regex>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

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

			server icmp(socket(AF_INET,SOCK_RAW,IPPROTO_ICMP));


			char recv[MAX_LENGHT];
			
			memset(recv, 0, MAX_LENGHT);


			icmp.set_file_name(recv,MAX_LENGHT);

			ofstream icmp_file("k"+icmp.get_file_name(),ifstream::binary);


			size_t file_lenght = icmp.get_file_lenght();

			
			int act_length= (file_lenght > MAX_LENGHT-sizeof(icmphdr)-20)? MAX_LENGHT - sizeof(icmphdr) -20 : file_lenght;
			int c;
			while(file_lenght > 0){

				cout<<"f:"<<file_lenght<<endl;
				//cout<<"act:"<<act_length<<endl;
				memset(recv, 0, MAX_LENGHT);
				c = icmp.read_packet(recv,act_length+20+sizeof(icmphdr));
				cout<<c<<endl;
				c-=20+sizeof(icmphdr);

				act_length = (file_lenght > MAX_LENGHT-sizeof(icmphdr)-20)? MAX_LENGHT - sizeof(icmphdr) -20 : file_lenght;

    			file_lenght -= c;

				

				icmp_file.write(recv+sizeof(icmphdr)+20,c);
			
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

	
		icmp_file.seekg (0, icmp_file.end);
    	size_t length = icmp_file.tellg();
    	icmp_file.seekg (0, icmp_file.beg);

    	char buffer[MAX_LENGHT];

    	icmp.send_file(sock,length,buffer);

    	int act_length;
    	
   			while(length){

    		act_length = (length > MAX_LENGHT-sizeof(icmphdr)-20)? MAX_LENGHT - sizeof(icmphdr) -20 : length;

    		length -= act_length;
    		//cout<<act_length;
    		icmp_file.read(buffer + sizeof(icmphdr),act_length);

			struct icmphdr *icmp_header = (struct icmphdr *)buffer;
			//cout<<sizeof(struct icmphdr *)<<endl<<sizeof(icmphdr);

			icmp_header->code = ICMP_ECHO;
			icmp_header->checksum = 0;
			cout<<(sizeof(icmphdr)+act_length)<<endl;
			icmp.send(sock,buffer,sizeof(icmphdr)+act_length);



		}
	
	

    	

    	
    	
	}
	
			
}