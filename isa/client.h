#include <memory>
#include <tuple>
#include <string>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>


class client{
	
	std::string host;
	std::string file;
	int icmp_protocol;

	char ip [32];
	struct addrinfo hints;
    struct addrinfo *res;
	public:
	int send(int sock , char * packet , size_t len);
	client(const std::string ip, const std::string f,const int ai_family,const int ai_socktype);
	const std::string  get_ip_hostname();
	const std::string  get_file();
	bool get_info();
	int get_sock();
	std::string get_ip();

};
