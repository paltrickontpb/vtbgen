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
	std::cout << "Project Testbench Aborted.\n[Exiting Now].."<< std::endl;
}

std::string getModuleName(char *module){
	std::string buffer = "";
	std::ifstream verilogFile;
	std::string filename, word;
	filename = module;
	verilogFile.open(filename.c_str()); 
	int count=0;
	while (verilogFile >> word){
		buffer += word;
		if (word=="endmodule") break;
		buffer += " ";
	}
	//Buffer prepared with module values
	std::smatch match;
	std::regex re("(module )([A-Za-z0-9_]+)((.*);)(.*)");
	if (regex_search(buffer, match, re) == true) { 
		return match.str(2);
	} else {
		return "Error"; 
	}
}

int generate_tb(std::string moduleName, std::vector<std::string> inputList, std::vector<std::string>outputList){
	std::string fileName = moduleName + "_tb.v";
	std::ofstream tbFile;
	tbFile.open(fileName, std::ofstream::out | std::ofstream::trunc);

	if (tbFile.is_open()){
		tbFile << "module " + fileName;
		tbFile.seekp(-2, std::ios_base::cur);
		tbFile << "();\n\n";
		//Input reg, output wire logic
		for(auto &itr : inputList){
			tbFile << "\treg "+ itr + ";\n";
		}
		for(auto &itr : outputList){
			tbFile << "\twire "+ itr + ";\n";
		}
		tbFile << "\n";
		tbFile << "\t" + moduleName + " UUT (";
		//Add .input(input) and .output(output)
		for(auto &itr : inputList){
			tbFile << "." + itr + "(" + itr + "),";
		}
		for(auto &itr : outputList){
			tbFile << "." + itr + "(" + itr + "),";
		}
		tbFile.seekp(-1, std::ios_base::cur);
		tbFile << ");\n\n";

		tbFile << "\t//Uncomment Next Line to add clock/continuously inverting signal\n";
    	tbFile << "\t//always @10 clk=~clk;\n\n";
		
		tbFile << "\tinitial begin\n";
		tbFile << "\t\t//Set input test cases under this line.\n\n";
		tbFile << "\t\t$finish; //Don't delete this directive\n";
		tbFile << "\tend\n\n";
    	    	
    	tbFile << "endmodule\n";
    	tbFile.close();
    	return 0;
	} else {
		std::cout << "Unable to open file";
		return 1;
	}
}