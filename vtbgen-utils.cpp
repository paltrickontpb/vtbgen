#include "vtbgen-utils.h"

int moduleCount(char* module){
	unsigned int count = 0;
	std::ifstream verilogFile;
	std::string word, filename;
	filename = module; 
    verilogFile.open(filename.c_str()); 
    while (verilogFile >> word) { 
        if(word == "module") count++;
    } 
    verilogFile.close();
	return count;
}

void callError(std::string err){
	std::cout << "Error : " << err << std::endl;
	std::cout << std::endl;
	std::cout << "Project Testbench Aborted. \n[Exiting Now].."<< std::endl;
}

std::string getModuleName(char *module){
	std::string databuf;
	std::ifstream verilogFile;
	std::string filename, line;
	filename = module;
	return "dff";
}