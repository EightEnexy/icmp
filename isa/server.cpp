#include "server.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>


server::server(int sock,int sock2){
	this->sock = sock;
	this->sock2 = sock2;	
}

int server::read_packet(char * recv,size_t size){

	file_lenght = recvfrom(sock,recv, size, 0,(sockaddr *)&addr, &addr_len);
	
	/*//TODO
	char buffer[31];

	memset(buffer, 0, 31);

	struct icmphdr *icmp_header = (struct icmphdr *)buffer;
	icmp_header->code = ICMP_ECHO;

	
	strcpy(buffer + sizeof(icmphdr),"OK");
	
    sendto(sock2, buffer, sizeof(buffer), 0,(struct sockaddr *)&addr, sizeof(addr));

    std::cout<<file_lenght<<std::endl;
    */
	return file_lenght;
}

bool server::set_file_name(char * recv , size_t size){
	
	int len = read_packet(recv,size);

	if (len < 0)
		return false;

	std::string str = (recv + ICMPHDR);
      
    std::vector <std::string> tokens;
      
    std::stringstream select(str);
      
    std::string token;
      
   
    while(getline(select, token,'\n'))
    {
        tokens.push_back(token);
    }
      
    if(tokens.size() != 4 )
    	return false;

    if(check_name(tokens[0]))
    	return false;

    if(check_lenght(tokens[2]))
    	return false;

    file_name = tokens[1];
    
    file_lenght = stoi(tokens[3]);



	return true;
}


