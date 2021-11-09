#include "server.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>


server::server(int sock){
	this->sock = sock;	
}

int server::read_packet(char * recv,size_t size){

	file_lenght = recvfrom(sock,recv, size, 0,(sockaddr *)&addr, &addr_len);
	return file_lenght;
}

bool server::set_file_name(char * recv , size_t size){
	
	int len = read_packet(recv,size);
	if (len < 0)
		return false;

	//reference: https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
	std::string str = (recv + sizeof(icmphdr) + 20);
      
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


