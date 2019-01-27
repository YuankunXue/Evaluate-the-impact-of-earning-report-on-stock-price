//
//  main.cpp
//  Project_6883
//

#include <iostream>
#include "libcurl.hpp"
#include "Stock.hpp"
#include "ReadCSV.hpp"
#include <stdio.h>
#include <map>
#include "CAAR.hpp"
#include "gnuplotnew.h"
using namespace std;
//Operator overloading in order to cout vector<double>
ostream & operator << (ostream & out, vector<double> r)
{
    for(vector<double>::iterator itr=r.begin();itr!=r.end();++itr)
        out<<*itr<<endl;
    return out;
}
//Operator overloading in order to cout vector<TradingData>
ostream & operator << (ostream & out, vector<TradingData> r)
{
    for(vector<TradingData>::iterator itr=r.begin();itr!=r.end();++itr)
        out<<*itr<<endl;
    return out;
}
//Def Matrix which we use to store AAR CAAR vector of three groups
typedef vector<vector<double>> Matrix;

//main function
int main()
{
    //Define char
    char selection;
    
    //initialize Map
    map<string,Stock> Beat_Map;
    map<string,Stock> Meet_Map;
    map<string,Stock> Miss_Map;
    
    //initialize vector which we push back data we get from CSV to
    vector<string> SymbolList;
    vector<string> ReportdateList;
    vector<double> EstiEPSList;
    vector<double> EPSList;
    
    //Read CSV and store the data in the vector
    ReadCSV(SymbolList,ReportdateList,EstiEPSList,EPSList);
    
    //Initialize variable preparing for Function 2
    string StockName;
    auto it=Beat_Map.begin();
    vector<vector<TradingData>> Hist_Price_Collection;

    //Download IWB data
    vector<string> DateVec=ReadCSV();
    vector<double> RIWB;
    vector<TradingData> IWB_Hist_Price;//calculate return of IWB
    IWB_Hist_Price=libcurl("IWB", DateVec[0], DateVec[DateVec.size()-1]); //extract the data of IWB
    
    //Calculate IWB Return
    for(vector<TradingData>::iterator itr=IWB_Hist_Price.begin();itr!=IWB_Hist_Price.end()-1;++itr)
    {
        RIWB.push_back(((itr+1)->price-itr->price)/itr->price);
    }
    
    //Initialize Object preparing for Function 3
    CAAR Beat(Beat_Map,RIWB);
    CAAR Meet(Meet_Map,RIWB);
    CAAR Miss(Miss_Map,RIWB);
    
    //Initialize variables preparing for Function 3
    string GroupName;
    string Indicator;
    
    //Initialize AAR Matrix and CAAR matrix
    Matrix AARMat(3);
    Matrix CAARMat(3);
    
    //Menu Do-While
    do
    {
        //Menu Initialization
        cout << "  6883 Team Project Menu"<<endl;
        cout << "  ===================================="<<endl;
        cout << "  1.  Retrieve Data"<<endl;
        cout << "  2.  Get Historical Data"<<endl;
        cout << "  3.  Show AAR/CAAR of each group"<<endl;
        cout << "  4.  Show the graph with CAAR for all 3 groups"<<endl;
        cout << "  5.  Exit"<<endl;;
        cout << "  ===================================="<<endl;
        cout << "  Enter your selection: ";
        cin >> selection;
        cout << endl;
        
        //Cases
        switch (selection)
        {
            case '1':
                cout << "Retrieve Data"<<endl;
                cout << "\n";
                //Retrieve Data
                Hist_Price_Collection=libcurl(SymbolList, ReportdateList, DateVec);
                for(int i=0;i<SymbolList.size();i++) //import data of the stocks
                {
                    Stock stk(SymbolList[i],ReportdateList[i],EstiEPSList[i],EPSList[i]);
                    stk.Hist_Price=Hist_Price_Collection[i];
                    
                    //Calculate Return of each Stock
                    for(vector<TradingData>::iterator itr=stk.Hist_Price.begin();itr!=stk.Hist_Price.end()-1;++itr)
                    {
                        stk.r.push_back(((itr+1)->price-itr->price)/itr->price);
                    }
                    
                    //Group the Stock
                    if(stk.type=="Beat")
                        Beat_Map[stk.symbol]=stk;
                    else if(stk.type=="Meet")
                        Meet_Map[stk.symbol]=stk;
                    else if(stk.type=="Miss")
                        Miss_Map[stk.symbol]=stk;
                    
                }
                //Pass the data to the map
                Beat.map=Beat_Map;
                Meet.map=Meet_Map;
                Miss.map=Miss_Map;
                //Calculate AAR CAAR
                CAARMat[0]=Beat.CalculateCAAR();
                CAARMat[1]=Meet.CalculateCAAR();
                CAARMat[2]=Miss.CalculateCAAR();
                AARMat[0]=Beat.Calculate_AAR();
                AARMat[1]=Meet.Calculate_AAR();
                AARMat[2]=Miss.Calculate_AAR();
                
                cout << "Well Done" <<endl;
                cout << "Finished Retrieveing Data"<<endl;
                break;
                
            case '2':
                cout << "Getting Historical data"<<endl;
                cout << "Enter the Stock Symbol: ";
                cin  >> StockName;
                it=Beat_Map.find(StockName);
                //Find out which group the stock belongs to
                if(it!=Beat_Map.end())
                {
                    cout<<"The Historical Data of "<<StockName<<" is : "<<endl;
                    cout<<it->second.Hist_Price;
                    cout<<endl;
                    cout<<"The Report Date of "<<StockName<<" is : "<<it->second.report_date<<endl;
                    cout<<"The Actual EPS of "<<StockName<<" is : "<<it->second.actual_eps<<endl;
                    cout<<"The Estimate EPS of "<<StockName<<" is : "<<it->second.est_eps<<endl;
                    cout<<"The Surprise percentage of "<<StockName<<" is : "<<it->second.surprise<<endl;
                    cout<<"The Group of "<<StockName<<" is : "<<it->second.type<<endl;
                }
                else
                {
                    it=Meet_Map.find(StockName);
                    if(it!=Meet_Map.end())
                    {
                        cout<<"The Historical Data of "<<StockName<<" is : "<<endl;
                        cout<<it->second.Hist_Price;
                        cout<<endl;
                        cout<<"The Report Date of "<<StockName<<" is : "<<it->second.report_date<<endl;
                        cout<<"The Actual EPS of "<<StockName<<" is : "<<it->second.actual_eps<<endl;
                        cout<<"The Estimate EPS of "<<StockName<<" is : "<<it->second.est_eps<<endl;
                        cout<<"The Surprise percentage of "<<StockName<<" is : "<<it->second.surprise<<endl;
                        cout<<"The Group of "<<StockName<<" is : "<<it->second.type<<endl;
                        
                    }
                    else
                    {
                        it=Miss_Map.find(StockName);
                        if(it!=Miss_Map.end())
                        {
                            cout<<"The Historical Data of "<<StockName<<" is : "<<endl;
                            cout<<it->second.Hist_Price;
                            cout<<endl;
                            cout<<"The Report Date of "<<StockName<<" is : "<<it->second.report_date<<endl;
                            cout<<"The Actual EPS of "<<StockName<<" is : "<<it->second.actual_eps<<endl;
                            cout<<"The Estimate EPS of "<<StockName<<" is : "<<it->second.est_eps<<endl;
                            cout<<"The Surprise percentage of "<<StockName<<" is : "<<it->second.surprise<<endl;
                            cout<<"The Group of "<<StockName<<" is : "<<it->second.type<<endl;
                            
                        }
                        else
                        {
                            cout<<"The Stock is not in the list"<<endl;
                        }
                    }
                }
                break;
            case '3':
                cout<<"Which group do you want to show? "<<endl;
                cout<<"Group One: Beat"<<endl;
                cout<<"Gouup Two: Meet"<<endl;
                cout<<"Group Three: Miss"<<endl;
                cin>>GroupName;
                cout<<"Which Indicator do you want to show? "<<endl;
                cout<<"Indicator One: AAR"<<endl;
                cout<<"Indicator Two: CAAR"<<endl;
                cin>>Indicator;
                if(GroupName == "Beat")
                {
                    if(Indicator == "CAAR")
                    {
                        cout<<CAARMat[0]<<endl;
                    }
                    else
                    {
                        cout<<AARMat[0]<<endl;
                    }
                }
                else if(GroupName == "Meet")
                {
                    if(Indicator == "CAAR")
                    {
                        cout<<CAARMat[1]<<endl;
                    }
                    else
                    {
                        cout<<AARMat[1]<<endl;
                    }
                }
                else if(GroupName == "Miss")
                {
                    if(Indicator == "CAAR")
                    {
                        cout<<CAARMat[2]<<endl;
                    }
                    else
                    {
                        cout<<AARMat[2]<<endl;
                    }
                }
                break;
            case '4':
                cout<<"Here is the graph with CAAR for all 3 groups "<<endl;
                cout<<"Press Enter to continue"<<endl;
                plotresults(CAARMat, 241);
                
                break;
                
                
                
            case '5':
                cout << "Exit the Program" ;
                cout << "\n";
                return 0;
                
            default: cout <<selection << "is not a valid menu item.\n";
                
                cout << endl;
        }
        
    }while (selection != 0);
    
    
    
    
    return 0;
}
