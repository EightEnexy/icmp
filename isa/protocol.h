#include <iostream>
#include <string>
#pragma once
#define MAX_LENGHT 1500
class protocol {
	public:
		bool check_name(std::string str);
		bool check_lenght(std::string str);
		char * set_name(std::string str);
		char * set_lenght(std::string str);
		
	protected:
    	inline static const std::string NAME = "\tFILE_NAME:\n";
		inline static const std::string LENGHT = "\tFILE_LENGHT:\n";
};	