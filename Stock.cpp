//
//  Stock.cpp
//  Project_6883
//

#include "Stock.hpp"
#include "libcurl.hpp"
#include "ReadCSV.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

//default constructor
Stock::Stock()
{
    symbol={};
    report_date={};
    est_eps=0;
    actual_eps=0;
    Hist_Price={};
}

//import DateVec vector from data_6883.csv file
vector<string> DateVec=ReadCSV();

//constructor with parameter
Stock::Stock(string symbol_,string report_date_,double est_eps_,double actual_eps_)
{
    symbol=symbol_;
    report_date=report_date_;
    est_eps=est_eps_;
    actual_eps=actual_eps_;
    //calculate EPS surprise for each stock
    if(est_eps_>=0 && actual_eps_>=0)
    {
        surprise=(actual_eps_-est_eps_)/est_eps_;
    }
    else if(est_eps_<0 && actual_eps_<0)
    {
        surprise=-((actual_eps_-est_eps_)/est_eps_);
    }
    else if (est_eps_>=0 &&actual_eps_<0)
    {
        surprise=(actual_eps_-est_eps_)/est_eps_;
    }
    else
    {
        surprise=-((actual_eps_-est_eps_)/est_eps_);
    }
    // grouping each stock
    if(surprise>0.05)
    {
        type="Beat";
    }
    else if(surprise<-0.05)
    {
        type="Miss";
    }
    else
    {
        type="Meet";
    }
    
    
    //find the address of report_date in the vector
    
    for(int i=0;i<DateVec.size();i++)
    {
        if(DateVec[i] == report_date)
        {
            DateLoc=i;
        }
    }
    
}
