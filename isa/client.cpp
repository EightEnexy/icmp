#include "client.h"
#include <cstring>
#include <iostream>

void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in *)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

client::client(const std::string ip, const std::string f,const int ai_family,const int ai_socktype){
	host = ip;
	file = f;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = ai_family;    
	hints.ai_socktype = ai_socktype; 
}

bool client::get_info(){


	if ((getaddrinfo(host.data(), NULL, &hints, &res)) != 0)
	{
		return false;

	}
	return true;
}

std::string client::get_ip(){
	

	struct sockaddr * addr = res->ai_addr;

	const bool ipv4 = (addr->sa_family == AF_INET);
	
	void * ipv = (ipv4) ? (void *)&(((struct sockaddr_in *)addr)->sin_addr) : (void *)&(((struct sockaddr_in6 *)addr)->sin6_addr);
	
	if(ipv4)
		icmp_protocol = IPPROTO_ICMP;
	else
		icmp_protocol = IPPROTO_ICMPV6;

	
	inet_ntop(res->ai_family,ipv, ip, sizeof(ip));
	return ip;
}

int client::get_sock(){

	return socket(res->ai_family, res->ai_socktype, icmp_protocol);

}

int client::send(int sock ,char * packet , size_t len){

	return  sendto(sock, packet, len, 0, (struct sockaddr *)(res->ai_addr), res->ai_addrlen);
	

	
} 
const std::string client::get_ip_hostname(){return host.data();}

const std::string client::get_file(){return file.data();}