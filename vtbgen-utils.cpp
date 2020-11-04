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

int getModuleName(char *module, std::string &moduleName, std::string &moduleArgs, std::string &moduleCode){
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
	std::smatch match;
	std::regex re("(.*)(module )([A-Za-z0-9_]+)(.*?);(.*)");
	if (regex_search(buffer, match, re) == true) { 
		moduleName = match.str(3);
		moduleArgs = match.str(4);
		moduleCode = match.str(5);
		return 0;
	} else {
		return 1; 
	}
}


int createIOList(std::string moduleArgs, std::string moduleCode, std::vector<std::string> &inputList, std::vector<std::string>  &outList){
	// Cleaning module IO set
	moduleArgs.erase(0,1); moduleArgs.resize(moduleArgs.size()-1);
	moduleArgs += '\0';

	// Push all IO to fullIO list
	std::string word = "";
	std::vector<std::string> fullIO;
	for (auto x: moduleArgs){
		if (x == ' ' || x == ',' || x == '\0'){
			if (word != "") fullIO.push_back(word);
			word = "";
		} else {
			word = word + x;
		}
	}

	// Parse module Code
	std::vector<std::string> codeArray;
	moduleCode += '\0';
	for (auto x: moduleCode){
		if (x == ' ' || x == ',' || x == ';' || x == '\0'){
			if (word != "") codeArray.push_back(word);
			word = "";
		} else {
			word = word + x;
		}
	}
	
	// Segregate IO List to inputs and outputs
	for (int len=0; len<fullIO.size(); len++){
		int i = 0;
		int pos = 0;
		for (auto x: codeArray){
			if( x.compare(fullIO[len]) == 0){
				pos = i;
				break;
			}
			i++;
		}
		std::string a = "input", b = "output";

		while(pos != -1) {
			if (codeArray[pos].compare(a) == 0){
				//std::cout << codeArray[pos] << std::endl;
				inputList.push_back(fullIO[len]);
				break;
			} else if (codeArray[pos].compare(b) == 0){
				//std::cout << codeArray[pos] << std::endl;
				outList.push_back(fullIO[len]);
				break;
			}
			pos-=1;
		}
		if (pos==-1) return 1;
	}
	
	return 0;
}

int generate_tb(std::string verilogFileName, std::string moduleName, std::vector<std::string> inputList, std::vector<std::string> outputList){
	std::string fileName = moduleName + "_tb.v";
	std::ofstream tbFile;
	tbFile.open(fileName, std::ofstream::out | std::ofstream::trunc);

	if (tbFile.is_open()){
		tbFile << "`include \"" + verilogFileName + "\"\n\n";
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