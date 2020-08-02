#ifndef _VTBGEN_UTILS_H_
#define _VTBGEN_UTILS_H_

#include <iostream>
#include <fstream>
#include <string>
#include "vtbgen.h"
#include "vtbgen-regex.h"

int moduleCount(char *module);
void callError(std::string err);
std::string getModuleName(char *module);

#endif