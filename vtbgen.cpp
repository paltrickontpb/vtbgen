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
	if(mCount == 0){
		callError("File doesn't contain any verilog module (Error Code : 03)");
		return 0;
	} else if(mCount > 1){
		cout << "Multiple Verilog modules were found. Please enter the top module name : ";
		cin >> moduleName;
	} else {
		moduleName = getModuleName(argv[1]);
	}
	cout << "Top Module Testbench Generation will be for " << moduleName << endl;

	cout << endl;
	cout << "Project Testbench Generated Successfully. \nExiting Now..."<< endl;
	return 0;
}