#include <memory>
#include <tuple>
#include <string>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/cdefs.h>
#include <sys/poll.h>
#include "protocol.h"
#include <netinet/ip_icmp.h>
#define IPV4_6 2

class server: public protocol {

	
	std::string file_name;
	int file_lenght;
	int sock;
	struct pollfd socks[IPV4_6];
	struct sockaddr_in  addr;
	int protocol;
	unsigned ihl;
	socklen_t addr_len = sizeof(struct sockaddr_in);

	public:
		int first_read(int sock,int sock2,char * recv,size_t size);
		int get_sock(){return sock;};
		int get_file_lenght(){return file_lenght;};
		std::string get_file_name(){return file_name;};
		int read_packet(char * recv,size_t size);
		bool set_file_name(char * recv , size_t size);
		size_t get_ihl(){return ihl;};


};
