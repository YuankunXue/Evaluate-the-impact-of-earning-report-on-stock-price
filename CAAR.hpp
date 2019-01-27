//
//  CAAR.hpp
//  6883
//

#ifndef CAAR_h
#define CAAR_h
#include "Stock.hpp"
#include <vector>
#include <map>
#include <iostream>
#include "ReadCSV.hpp"
#include "libcurl.hpp"
using namespace std;
class CAAR
{
public:
    //constructor with parameter
    CAAR(map<string,Stock> map_,vector<double> RIWB_)
    {
        map=map_;
        RIWB=RIWB_;
    }
    //store the symbol list of each group
    vector<string> symbol;
    //store the Return of each stock in the group
    vector<vector<vector<double>>> Rit;
    //store the position that use to find the location in RIWB
    vector<vector<int>> Findloc;
    //The RIWB: Return of IWB
    vector<double> RIWB;
    //Store AAR
    vector<vector<double>> AAR;
    //Store CAAR
    vector<vector<double>> CAARMatrix;
    //The map we pass to the constructor
    map<string,Stock> map;
    //store the Five randomly selected symbol list
    vector<vector <string>> random_t;
    //Store the CAAR Average
    vector<double> CAAR_ave;
    //Member function: Calculate CAAR
    vector<double> CalculateCAAR();
    //Member function: Calculate AAR(Average)
    vector<double> Calculate_AAR();
};
//Function : Random select
vector<string> random_select(vector<string> symbol);//random select function
#endif /* CAAR_h */
