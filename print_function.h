#include <iostream>
#include <vector>
#include "header.h"
#pragma once 

using namespace std;

void print_board(vector<vector<char> > board)                   // It is not straight forward to print the board.
                                                                // The board is such that board[i][j] represents
                                                                // jth cell of the ith block.
                                                                // But while printing we need to print a block
                                                                // as a 3X3 matrix.
{
    char mat[9][9];
    for(int i=0;i<9;i++)
    {
        int outrow=i/3;
        int outcol=i%3;
        for(int j=0;j<9;j++)
        {
            int col=j%3;
            int row=j/3;
            mat[3*outrow+row][3*outcol+col] = board[i][j];
        }
    }
    for (int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(j==3 || j==6)
                cout<<"    ";
            else if(j==0)
                cout << "\t\t\t\t ";
            else 
                cout << " ";
            cout<< mat[i][j] ;
        }
        cout<<endl;
        if(i==2 || i==5)
            cout<<endl;
    }
    cout<<endl;
}
