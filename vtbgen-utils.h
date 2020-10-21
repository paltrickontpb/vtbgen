#ifndef _VTBGEN_UTILS_H_
#define _VTBGEN_UTILS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 
#include "vtbgen.h"

int moduleCount(char *module);
void callError(std::string err);
std::string getModuleName(char *module);
int generate_tb(std::string moduleName);

#endif