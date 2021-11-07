#include "prog_parse.h"
#include <iostream>
#include <algorithm>

const opt prog::get_opt(char * argv){

	for (auto & opt : opts)
	{
		if(!(opt->get_name()).compare(argv))
			return *opt;
	}
	return opt{err()};

}

bool prog::check_count(int argc){

	for(std::string supp_opt : supp_opts){
		 if (static_cast<int>(supp_opt.length())  == argc -1 ){
		 	return true;
		 }
	
	}
	return false;
}

bool prog::parse(int argc,char*argv[]){

 	if (argc == 1)
 		return false;

	for(int i = 1 ; i < argc ; i++){

		auto opt = get_opt(argv[i]);
		
		remove_supp_opt(opt);

		if (!opt.get_name().compare(err()))
			return false;

		if (!check_count(argc))
			return false;
			
		if (args.find(opt.get_name()) != args.end())
			return false;

		if(opt.get_arg())
			args[opt.get_name()] = argv[++i];

	}

	return true;

}

void prog::remove_supp_opt(opt th_opt){

	for (auto it = supp_opts.begin(); it != supp_opts.end();  ++it )
	{	
        	std::size_t found = it->find(th_opt.get_supp_name());
  		
  	  		if (found==std::string::npos){
  				supp_opts.erase(it);
  				it = supp_opts.begin();

  			}     
	}

}

const std::string prog::err(){
	return "error";
}

bool prog::get_supp_opt(const char opt){
	for(std::string opt_ord : supp_opts){		
		if(opt_ord.find(opt))
			return true;
	}
	return false;
}
