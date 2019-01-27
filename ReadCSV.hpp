//
//  ReadCSV.hpp
//  Project_6883
//

#ifndef ReadCSV_hpp
#define ReadCSV_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int ReadCSV(vector<string> &SymbolList,vector<string> &ReportdateList,vector<double> &EstiEPSList,vector<double> &EPSList);
vector<string> ReadCSV();
#endif /* ReadCSV_hpp */
