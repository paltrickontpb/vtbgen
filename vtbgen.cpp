#include "vtbgen.h"

using namespace std;

int main(int argc, char** argv){
	cout << endl;
	cout << "========================================================" << endl;
	cout << "=========== Open Verilog Testbench Generator ===========" << endl;
	cout << "========================================================" << endl;
	cout << endl;
	if(argc != 2){
		callError("Please Input the File Containing the Top Module (Error Code : 02)");
		return 0;
	}
	cout << "Entered File Name : " << argv[1] << endl;
	cout << "Extracting Verilog Modules List" << endl;
	cout << endl;
	unsigned int mCount = moduleCount(argv[1]);
	cout << "No. of Modules present : " << mCount << endl;
	cout << endl;

	string moduleName;
	string moduleArgs;
	string moduleCode;
	if(mCount == 0){
		callError("File doesn't contain any verilog module (Error Code : 03)");
		return 0;
	} else if(mCount > 1){
		cout << "Multiple Verilog modules were found. Multi-module support is under development";
		cout << endl;
		return 0;
	} else {
		int moduleResponse = getModuleName(argv[1], moduleName, moduleArgs, moduleCode);
		if (moduleResponse == 1) {
			cout << "Module Name not picked up. Error handling will be added in later version ";
			//cin >> moduleName;
			cout << endl;
			return 0;
		}
	}
	cout << "\nTop Module Testbench Generation will be for " << moduleName << endl;

	//add input/output vector of strings
	std::vector<std::string> inputList;
	std::vector<std::string> outList;
	int responseCode = createIOList(moduleArgs, moduleCode, inputList, outList);
	if(responseCode == 0) {
		int genResponse = generate_tb(argv[1], moduleName, inputList, outList);
		if(genResponse == 0){
			cout << "\nProject Testbench Generated Successfully. \nExiting Now..."<< endl;
			return 0;
		} else {
			callError("Module Error (Error Code : 06)");
			return 1;
		}
	} else {
		callError("Module Error (Error Code : 06)");
		return 1;
	}
	return 0;
	// TESTING 
	/*
	std::vector<std::string> b;
	std::vector<std::string> c;
	b.push_back("input1");
	b.push_back("input2");
	c.push_back("output1");
	c.push_back("output2"); */
	//int a = generate_tb(argv[1], moduleName, b, c);
	//cout << a << endl;
	// END TEST
	
}