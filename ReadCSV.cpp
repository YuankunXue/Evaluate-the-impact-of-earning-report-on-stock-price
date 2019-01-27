//
//  ReadCSV.cpp
//  Project_6883
//

#include <stdio.h>
#include "ReadCSV.hpp"
//Read CSV Data Got from Bloomberg and store them into vector
int ReadCSV(vector<string> &SymbolList,vector<string> &ReportdateList,vector<double> &EstiEPSList,vector<double> &EPSList)
{
    //open the file and check if it is opened successfully
    ifstream ifs("data_6883.csv");
    if (!ifs.is_open()) {
        cerr << "Open data_6883.csv Failed" << endl;
        system("pause");
        return 1;
    }
    
    //prepare for reading data from CSV
    vector<string> DateList;
    string line;
    getline(ifs, line); //ignore first line
    while (getline(ifs, line))
    {
        istringstream ss_line(line);
        string item = "";
        
        //Get symbol
        getline(ss_line, item, ',');
        string symbol = item;
        SymbolList.push_back(symbol);
        
        //Get Report_date
        getline(ss_line, item, ',');
        string report_date = item;
        ReportdateList.push_back(report_date);
        
        //Get date
        getline(ss_line, item, ',');
        string date = item;
        DateList.push_back(date);
        
        //Get Est EPS
        getline(ss_line, item, ',');
        double est_earning = stod(item);
        EstiEPSList.push_back(est_earning);
        
        //Get Real EPS
        getline(ss_line, item, ',');
        double earning = stod(item);
        EPSList.push_back(earning);
        
    }
    //erase unnecessary elements
    DateList.erase(DateList.end()-466,DateList.end());
    return 0;
    
    
}

//overloading the function in order to get DateVec!
vector<string> ReadCSV()
{
    ifstream ifs("data_6883.csv");
    if (!ifs.is_open()) {
        cerr << "Open data_6883.csv Failed" << endl;
        system("pause");
        return vector<string>{"1"};
    }
    vector<string> DateList;
    vector<string> SymbolList;
    vector<string> ReportdateList;
    vector<double> EPSList;
    vector<double> EstiEPSList;
    string line;
    getline(ifs, line); //ignore first line
    while (getline(ifs, line))
    {
        istringstream ss_line(line);
        string item = "";
        
        getline(ss_line, item, ',');
        string symbol = item;
        SymbolList.push_back(symbol);
        
        getline(ss_line, item, ',');
        string report_date = item;
        ReportdateList.push_back(report_date);
        
        getline(ss_line, item, ',');
        string date = item;
        DateList.push_back(date);
        
        getline(ss_line, item, ',');
        double est_earning = stod(item);
        EstiEPSList.push_back(est_earning);
        
        getline(ss_line, item, ',');
        double earning = stod(item);
        EPSList.push_back(earning);
        
    }
    //erase unnecessary elements
    DateList.erase(DateList.end()-466,DateList.end());
    
    return DateList;
}
