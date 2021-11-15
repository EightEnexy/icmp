#include <iostream>
#include <string>
#include <cstring>
#include <openssl/aes.h>
#pragma once
#define MAX_LENGHT 1500
#define OFFSET 100
#define PACKET_MARK 12



class protocol {
	public:
		bool check_name(std::string str);
		bool check_lenght(std::string str);
		char * set_name(std::string str);
		char * set_lenght(std::string str);
		void encrypt_data(int size, char * const buffer);
		void decrypt_data(int size, char *buffer);
		void set_decrypt_key();
		void set_encrypt_key();
		void set_pn(const unsigned long pn,char * buffer);
		bool check_pn(const unsigned long pn,char * recv);
		
	protected:
		// encrypt / decrypt 
		AES_KEY decrypt;
		AES_KEY encrypt;
		inline static const char * key = "xdreng01";
		inline static const	size_t bit_size = 128;
		// protocol messages 
     	inline static const std::string NAME = "\tFILE_NAME:\n";
		inline static const std::string LENGHT = "\tFILE_LENGHT:\n";
		inline static const std::string PN = "PN";	
};	