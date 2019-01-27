//
//  gnuplotnew.h
//  Project_6883
//

#ifndef gnuplotnew_h
#define gnuplotnew_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<double>> Matrix;
//the function of plotting the graph of CAAR
void plotresults(Matrix C,int size_)
{
    ofstream fout;
    fout.open("CAAR.txt");//Associate the fout object with a specific file using the open method
    //enter data of value of horizontal axis,CAAR of Beat, Meet, Miss groups
    for (int i = 0; i < size_; i++)
    {
        fout << i - 120 << " " << C[0][i] << " " << C[1][i] << " " << C[2][i] << endl;
    }
    fout.close();//close file connection
    
    fout.open("Plot.txt");
    fout << "set title \"CAAR\"" << endl;
    //plot lines for CAAR of each group with specific title
    fout << "plot 'CAAR.txt' using 1:3 title 'Meet' with lines, 'CAAR.txt' using 1:2 title 'Beat' with lines, 'CAAR.txt' using 1:4 title 'Miss' with lines" << endl;
    fout << "pause -1" << endl;
    fout.close();//close file connection
    system("/opt/local/bin/gnuplot Plot.txt");
}




#endif /* gnuplotnew_h */
