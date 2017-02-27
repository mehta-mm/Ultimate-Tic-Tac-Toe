#include <iostream>
#include <vector>
#include "header.h"
#include "print_function.h"
#include "utility.h"

using namespace std;


result alpha_beta (vector<vector<char> >board, int block2)                      // Initial alpha beta function.
{
    int value = INT_MIN, temp;
    int block = 0;
    int cell = 0;
    bool check = false;

    if(new_game)
    {
        for (int i=0; i<limit; i++)
        {
            for(int j=0; j<limit; j++)                                  
            {
                board[i][j] = 'x';
                temp = min_value(board, INT_MIN, INT_MAX, j, 1);  // call the min for all positions.
                board[i][j] = '-';

                if(value <=  temp)
                {
                    value = temp;
                    block = i;
                    cell = j;
                }
            }
        }
        new_game = false;
        return result (block, cell);                               // Return the move that is most fruitful.
    }

    else
    {
        for(int j=0; j<limit; j++)
        {
            if(board[block2-1][j] == '-')
            {
                board[block2-1][j] = 'x';
                temp = min_value(board, INT_MIN, INT_MAX, j, 1);  // call the min function.
                board[block2-1][j] = '-';
                check = true;

                if(value <= temp)                                               // Pruning condition.
                {
                    value = temp;
                    block = block2-1;
                    cell = j;
                }
            }
        }
        if(check)
            cout << "The bot has to play in block " << block2 << endl;

        if(!check)                                                      // If all the positions are filled then 
                                                                        // the player can move anywhere.
        {
            cout << "The bot can play anywhere" << endl;
            for(int i=0; i<limit; i++)
            {
                for(int j=0; j<limit; j++)
                {
                    if(board[i][j] == '-')
                    {
                        board[i][j] = 'x';
                        temp = max(value, min_value(board, INT_MIN, INT_MAX, j, 1));
                        board[i][j] = '-';

                        if(value <= temp)                                               // Pruning condition.
                        {
                            value = temp;
                            block = i;
                            cell = j;
                        }
                    }
                }
            }
        }
        return result (block, cell);   
    }

    
}

int max_value (vector<vector<char> > board, int alpha, int beta, int block, int depth)
{
    bool check = false;

    if(depth == max_depth)                                          // Estimate the utility value.
    {   
        cout << endl <<endl <<endl;
        print_board(board);
        int utility2 = utility(board);
        cout << utility2;
        return utility2;
    }

    int value = INT_MIN;

    for(int j=0; j<limit; j++)
    {
        if(board[block][j] == '-')
        {
            board[block][j] = 'x';
            value = max(value, min_value(board, alpha, beta, j, depth+1));  // call the min function.
            board[block][j] = '-';
            check = true;

            if(value >= beta)                                               // Pruning condition.
            {
                return value;
            }
                
            alpha = max(alpha, value);
        }
        return value;
    }

    if(!check)                                                      // If all the positions are filled then 
                                                                    // the player can move anywhere.
    {
        for(int i=0; i<limit; i++)
        {
            for(int j=0; j<limit; j++)
            {
                if(board[i][j] == '-')
                {
                    board[i][j] = 'x';
                    value = max(value, min_value(board, alpha, beta, j, depth+1));
                    board[i][j] = '-';

                    if(value <=alpha)
                    {
                        return value;
                    }
                    beta = min(beta, value);
                }
                return value;
            }
        }
    }
} 

int min_value (vector<vector<char> > board, int alpha, int beta, int block, int depth)
{
    bool check = false;
    if(depth == max_depth)                                                  // Estimate the utility.
    {
        return utility(board);
    }              

    int value = INT_MAX;

    for(int j=0; j<limit; j++)
    {
        if(board[block][j] == '-')
        {
            board[block][j] = 'o';
            value = min(value, max_value(board, alpha, beta, j, depth+1));  // Call the max function
            board[block][j] = '-';
            check = true;

            if(value <=alpha)                                               // Pruning condition.
            {
                return value;
            }
            beta = min(beta, value);
        }
        return value;
    } 

    if(!check)                                                 // Can play anywhere if all positions in the 
                                                               // allowed blocks are filled.
    {
        for(int i=0; i<limit; i++)
        {
            for(int j=0; j<limit; j++)
            {
                if(board[i][j] == '-')
                {
                    board[i][j] = 'o';
                    value = min(value, max_value(board, alpha, beta, j, depth+1));  // Call the max function.
                    board[i][j] = '-';

                    if(value <=alpha)                           // Pruning function.
                    {
                        return value;
                    }
                    beta = min(beta, value);
                }
                return value;
            }
        }
    }
}