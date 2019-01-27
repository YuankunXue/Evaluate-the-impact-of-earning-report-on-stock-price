//
//  libcurl.hpp
//  Project_6883
//

#ifndef libcurl_hpp
#define libcurl_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>
#include "curl/curl.h"
#include "Stock.hpp"
using namespace std;
typedef vector<double> Vector;

struct MemoryStruct {
    char *memory;
    size_t size;
};
size_t write_data(void *ptr, int size, int nmemb, FILE *stream);
void *myrealloc(void *ptr, size_t size);
size_t write_data2(void *ptr, size_t size, size_t nmemb, void *data);
string getTimeinSeconds(string Time);
vector<vector<TradingData>> libcurl(vector<string> SymbolList,vector<string> ReportdateList,vector<string> DateVec); //retrieve data of each stock
//SymbolList is the vector that stores the symbol of each stock
//ReportdateList is the vector that stores the report_Date of each stock
//DateVec is the vector that stores all possible trading dates for our selected stocks.
//The return type is vector of vector of TradingData. It stores the price information of each stock for 242 trading dates.
vector<TradingData> libcurl(string Symbol,string start_time,string end_time); //retrieve data of the Index IWB.


#endif /* libcurl_hpp */
