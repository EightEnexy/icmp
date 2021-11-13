#include <memory>
#include <tuple>
#include <string>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/cdefs.h>
#include "protocol.h"
#include <netinet/ip_icmp.h>



class server: public protocol {

	
	std::string file_name;
	int file_lenght;
	int sock;
	int sock2;
	struct sockaddr_in  addr;
	socklen_t addr_len = sizeof(struct sockaddr_in);

	public:
		server(int sock,int sock2);
		int get_sock(){return sock;};
		int get_file_lenght(){return file_lenght;};
		std::string get_file_name(){return file_name;};
		int read_packet(char * recv,size_t size);
		bool set_file_name(char * recv , size_t size);


};
