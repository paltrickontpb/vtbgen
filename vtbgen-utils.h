#ifndef _VTBGEN_UTILS_H_
#define _VTBGEN_UTILS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <bits/stdc++.h> 
#include "vtbgen.h"

int moduleCount(char *module);
void callError(std::string err);
int getModuleName(char *module, std::string &moduleName, std::string &moduleArgs, std::string &moduleCode);
int generate_tb(std::string verilogFileName, std::string moduleName, std::vector<std::string> inputList, std::vector<std::string> outputList);
int createIOList(std::string moduleArgs, std::string moduleCode, std::vector<std::string> &inputList, std::vector<std::string>  &outList);

#endif