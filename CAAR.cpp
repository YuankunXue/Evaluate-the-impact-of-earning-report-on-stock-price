//
//  CAAR.cpp
//  6883
//

#include "CAAR.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <map>

using namespace std;
typedef vector<double> Vector;

vector<string> random_select(vector<string> symbol)
{
    do{
        symbol.erase(symbol.begin()+rand()%symbol.size());
    }
    while(symbol.size()>100);
    return symbol;
}

vector<double> CAAR::CalculateCAAR()
{
    // Extract the symbol in the map to the vector symbol
    for(std::map<string,Stock>::iterator it = map.begin(); it != map.end(); ++it)
    {
        symbol.push_back(it->first);
    }
    //Randomly screen 100 stocks
    random_t.resize(5);
    for (int i=0;i<5;i++)
    {
        random_t[i]=random_select(symbol);
    }
    //Put all stock return vectors in the rit vector;Put DateLoc in findloc vector.
    Rit.resize(5);
    Findloc.resize(5);
    for (int i=0;i<5;i++)
    {
        random_t[i].resize(100);
        for (int j=0;j<100;j++)
        {
            std::map<string,Stock>::iterator itr= map.find(random_t[i][j]);
            if(itr!=map.end())
            {
                Rit[i].push_back(itr->second.r);
                
                Findloc[i].push_back(itr->second.DateLoc-1);
            }
        }
    }
    //Calculate ARIT
    for (int i=0;i<5;i++)
    {
        //Rit[i].resize(100);
        Findloc[i].resize(100);
        for (int j=0;j<100;j++)
        {
            //Rit[i][j].resize(241);
            for (int m=0;m<241;m++)
            {
                Rit[i][j][m]=Rit[i][j][m]-(RIWB[Findloc[i][j]+m-120]);
            }
        }
    }
    //Calculate AAR
    AAR.resize(5);
    for (int i=0;i<5;i++)
    {
        AAR[i].resize(241);
        for(int m=0;m<241;m++)
        {
            for (int j=0;j<100;j++)
            {
                AAR[i][m]+=Rit[i][j][m];
            }
            AAR[i][m]=AAR[i][m]/100;
        };
    };
    
    //Calculate CAAR
    CAARMatrix.resize(5);
    for (int i=0;i<5;i++)
    {
        CAARMatrix[i].resize(241);
        for (int m = 0; m < 241; m++)
        {
            if (m == 0) {
                CAARMatrix[i][m] = AAR[i][m];
            }
            else {
                CAARMatrix[i][m] = CAARMatrix[i][m-1] + AAR[i][m];
            }
        }
    }
    // take the average of CAAR
    CAAR_ave.resize(241);
    for(int m = 0; m < 241; m++)
    {
        for (int i=0;i<5;i++)
        {
            CAAR_ave[m]+=CAARMatrix[i][m];
        }
        CAAR_ave[m]=CAAR_ave[m]/5;
    }
    return CAAR_ave;
}
// Calculate AAR
vector<double> CAAR::Calculate_AAR()
{
    vector<double> AAR_Avg(241);
    for(int m = 0; m < 241; m++)
    {
        for (int i=0;i<5;i++)
        {
            AAR_Avg[m]+=AAR[i][m];
        }
        AAR_Avg[m]=AAR_Avg[m]/5;
    }
    return AAR_Avg;
}
