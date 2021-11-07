#include <iostream>
#include <regex>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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


std::tuple<const char *,const char *> prog_client(const int argc,char *argv[]){

	return {argv[1],argv[2]};
}



int main(int argc,char*argv[]){

	using namespace std;
	
	prog prog({"r:s:","l"});

	if (!prog.parse(argc,argv))
		err_msg(arg);
	
		
	if (argc == SERVER){
		;
	}
	else{
		
		client icmp(prog.get_arg_by_key(IP_HOSTNAME),prog.get_arg_by_key(FILE),AF_UNSPEC,SOCK_RAW);
		
		if (!icmp.get_info())
			err_msg(cl);

		cout<<icmp.get_ip()<<endl;
		
		int sock;
		if((sock = icmp.get_sock()) == -1)
			err_msg(cl);

		char packet[1500];
		char data[] = "OMEGALUL";
		int datalen = 10;

		memset(&packet, 0, 1500);

		struct icmphdr *icmp_header = (struct icmphdr *)packet;

		icmp_header->code = ICMP_ECHO;
		icmp_header->checksum = 0;

		memcpy(packet + sizeof(struct icmphdr), data, datalen);

		icmp.send(sock,packet,sizeof(struct icmphdr) + datalen);
		
	}
	

	/*





	// MAXDATALEN = MTU(1500B) - zvyšna velkost čo si spotreboval :)

	if (sendto(sock, packet, sizeof(struct icmphdr) + datalen, 0, (struct sockaddr *)(serverinfo->ai_addr), serverinfo->ai_addrlen) < 0)
	{
		fprintf(stderr, "sendto err :)\n");
		return 1;
	}

	// //šifrovanie

	const unsigned char cyphertext[] = "Monntegea";
	int cyphertextlen = 10;

	AES_KEY key_e;
	AES_KEY key_d;
	AES_set_encrypt_key((const unsigned char *)"xlogin00", 128, &key_e);
	AES_set_decrypt_key((const unsigned char *)"xlogin00", 128, &key_d);

	unsigned char *output = (unsigned char *)calloc(cyphertextlen + (AES_BLOCK_SIZE % cyphertextlen), 1);

	AES_encrypt(cyphertext, output, &key_e);

	printf("encrypted: ");
	for (int i = 0; i < AES_BLOCK_SIZE; ++i)
	{
		printf("%X ", output[i]);
	}
	printf("\n");

	AES_decrypt(output, output, &key_d);

	printf("decrypted: %s\n", output);

	return 0;
	*/
}