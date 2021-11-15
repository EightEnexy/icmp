#include "server.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

int server::first_read(int sock,int sock2,char * recv,size_t size){
	// choosing sockets 
	socks[0].fd = sock2;
	socks[0].events = POLLIN;

	socks[1].fd = sock;
	socks[1].events = POLLIN;
		
	poll(socks,2,-1);
	int lenght = 0;

	if(socks[1].revents & POLLIN){
		this->sock = sock;
		lenght = recvfrom(this->sock,recv, size, 0,(sockaddr *)&addr, &addr_len);
		this->ihl = (recv[0] & 0x0F)*4;
	}

	if(socks[0].revents & POLLIN){
		this->sock = sock2;
		lenght = recvfrom(this->sock,recv, size, 0,(sockaddr *)&addr, &addr_len);
		this->ihl = 0;
	}
	
	return lenght;

}

int server::read_packet(char * recv,size_t size){

	file_lenght = recvfrom(sock,recv, size, 0,(sockaddr *)&addr, &addr_len);

	return file_lenght;
}

bool server::set_file_name(char * recv , size_t size){
	
	int len = first_read(socket(AF_INET,SOCK_RAW,IPPROTO_ICMP),socket(AF_INET6,SOCK_RAW,IPPROTO_ICMPV6),recv,size);

	if (len < 0)
		return false;
		
	// tokenizing strings 
	std::string str = (recv + ihl + sizeof(icmphdr));
	
    std::vector <std::string> tokens;
      
    std::stringstream select(str);
      
    std::string token;
      
   
    while(select >> token)
    {	
    	std::cout<<token<<std::flush;
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


