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

void protocol::set_pn(const unsigned long pn,char * buffer){

	std::string str_pn = PN + std::to_string(pn);
    memcpy(buffer,str_pn.data(),PACKET_MARK);

}

bool protocol::check_pn(const unsigned long pn,char * recv){

	std::string str_pn = PN + std::to_string(pn);
	if(!memcmp(recv,str_pn.data(),str_pn.size()))
		return true;

	return false;

}
void protocol::set_encrypt_key(){

	AES_set_encrypt_key((unsigned char *)key, bit_size, &encrypt);
}

void protocol::set_decrypt_key(){
	AES_set_decrypt_key((unsigned char *)key, bit_size, &decrypt);
}

void protocol::encrypt_data(int size,char *const buffer){

	unsigned char * encrypt_data = reinterpret_cast<unsigned char *>(buffer);
	
	for(int i = 0; i < ((size%AES_BLOCK_SIZE)? (size/AES_BLOCK_SIZE)+1 : (size/AES_BLOCK_SIZE)) ;i++){
			AES_encrypt(encrypt_data,encrypt_data, &encrypt);
			encrypt_data+=AES_BLOCK_SIZE;
		}
	
}
void protocol::decrypt_data(int size,char * buffer){
	
	unsigned char * dencrypt_data = reinterpret_cast<unsigned char *>(buffer);
		
	for(int i = 0; i < ((size%AES_BLOCK_SIZE)? (size/AES_BLOCK_SIZE)+1 : (size/AES_BLOCK_SIZE)) ;i++){
		AES_decrypt(dencrypt_data,dencrypt_data, &decrypt);
		dencrypt_data+=AES_BLOCK_SIZE;
	}
}