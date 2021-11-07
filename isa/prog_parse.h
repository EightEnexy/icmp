#include <string>
#include <unordered_map>
#include <vector>
#include <locale>
#include <iostream>

class opt{
	const std::string name;
	bool arg;
	public:
		opt(const std::string name):name{name} , arg{false} {}
		void set_arg(bool arg){  this -> arg = arg ;};
		const std::string  get_name(){return name;};
		bool get_arg(){return arg;};
		std::tuple<const std::string , const bool > get_name_arg(){ return {name,arg};};
		std::string get_supp_name(){return (arg)? std::string(1,name.at(1)) + ':' : std::string(1,name.at(1));};
};

class prog{
	
	std::unordered_map <std::string,std::string> args;
	std::vector<std::string> supp_opts;
	std::vector<std::unique_ptr<opt>> opts;

	public:
	prog (const std::vector<std::string> && supp_opts):
		 supp_opts{supp_opts}{
		 	for(std::string opt_ord : supp_opts){
		 		for (std::string::iterator it = opt_ord.begin() ; it != opt_ord.end(); ++it){
    				if (std::isalpha(*it)){
    					opts.push_back(std::make_unique<opt>(std::string(1,'-') + *it));
    				}
    				else if(*it == ':'){
    					opts.back()->set_arg(true);
    				}
    				else{
    					std::cerr << "invalid usage of prog" << std::endl;
						exit(0);
					}
			
		 }	}	}

	 std::string get_arg_by_key(std::string key){
					try{
						return args.at(key);
					}
					catch(const std::exception& key){
						std::cerr << "key dosen't exit" << std::endl;
						return err();
					}
				};
	std::vector<std::unique_ptr<opt>> const& get_opts(){return opts;};
	std::unordered_map <std::string,std::string> get_args(){return args;};
	bool parse(int argc,char*argv[]);
	bool check_count(int argc);
	const opt  get_opt(char * argv);
	const std::string err();
	void insert_opt(std::string);
	bool get_supp_opt(const char);
	void remove_supp_opt(opt th_opt);
};
