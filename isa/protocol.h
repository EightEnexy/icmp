#include <iostream>
#include <string>
#include <openssl/aes.h>
#pragma once
#define MAX_LENGHT 1500
#define OFFSET 100
#define ICMPHDR 28

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
		
	protected:
		AES_KEY decrypt;
		AES_KEY encrypt;
		inline static const char * key = "xdreng01";
		inline static const	size_t bit_size = 128;
     	inline static const std::string NAME = "\tFILE_NAME:\n";
		inline static const std::string LENGHT = "\tFILE_LENGHT:\n";
};	