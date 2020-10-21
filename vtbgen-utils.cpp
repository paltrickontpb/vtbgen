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

int generate_tb(std::string moduleName){
	std::string fileName = moduleName + "_tb.v";
	std::ofstream tbFile;
	tbFile.open(fileName, std::ofstream::out | std::ofstream::trunc);

	if (tbFile.is_open()){
		tbFile << "module "+fileName+"();\n";
		//Add input reg, output wire logic

		tbFile << moduleName+" UUt (";
		//Add .input(input) and .output(output)
		tbFile << " );\n\n"

		tbFile << "//Uncomment to Add Clock\n";
    	tbFile << "//always @10 clk=~clk;\n\n";
		
		tbFile << "initial begin\n"
		tbFile << "//Put initial input, output test cases here\n"
		tbFile << "#10\n"
		tbFile << "#10\n"
		tbFile << "#10\n\n"
		tbFile << "$finish; // End test\n"
		tbFile << "end\n\n"
    	    	
    	tbFile << "endmodule\n";
    	tbFile.close();
    	return 0;
	} else {
		std::cout << "Unable to open file";
		return 1;
	}
}