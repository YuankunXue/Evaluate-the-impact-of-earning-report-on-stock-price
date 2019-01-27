//
//  Stock.hpp
//  Project_6883
//

#ifndef Stock_hpp
#define Stock_hpp
#include <vector>
#include <string>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <map>
using namespace std;
// construct a class to store prices and corresponding dates for each stock
class TradingData
{
public:
    double price;
    string sDate;
    TradingData() : sDate(""), price(0.0) {}
    TradingData(string sDate_, double price_) : sDate(sDate_),price(price_){}
    
    double getClose()
    {
        return price;
    }
    // operator overloading
    TradingData operator&= (const TradingData & Data_)
    {
        price = Data_.price;
        sDate = Data_.sDate;
        return *this;
    }
    
    friend ostream & operator << (ostream & out,  TradingData  Data)
    {
        out<<Data.sDate<<" "<<Data.price<<endl;
        return out;
    }
    
};

class Stock
{
public:
    string symbol;
    vector<TradingData> Hist_Price;
    string report_date;
    string type;
    double actual_eps;
    double est_eps;
    double surprise; // for type grouping
    int DateLoc; // find date to compare with IWB return
    vector<double> r; // return for each stock
    
    Stock();
    Stock(string symbol_,string report_date_,double est_eps_,double actual_eps_);
};
#endif /* Stock_hpp */
