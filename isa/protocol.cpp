#include "protocol.h"

bool protocol::check_name(std::string name){
	return !name.compare(NAME);
}

bool protocol::check_lenght(std::string lenght){
	return !lenght.compare(LENGHT);
}

char * protocol::set_name(std::string name){
	name = NAME + name + "\n";
	return name.data();

}
char * protocol::set_lenght(std::string lenght){
	lenght = LENGHT + lenght + "\n";
	return lenght.data();
}