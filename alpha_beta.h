#include <iostream>
#include <vector>
#include "header.h"
#include "print_function.h"
#include "utility.h"

using namespace std;

result alpha_beta (vector<vector<char> >board, int block2)        // Initial alpha beta function.
{
    int value = INT_MIN, temp;
    int block = 0;
    int cell = 0;
    bool check = false;

    if(new_game)
    {
        cout << "\t\t\t   Doing Hashing of different states..." << endl;
        for (int i=0; i<limit; i++)
        {
            for(int j=0; j<limit; j++)                                  
            {
                board[i][j] = 'x';
                temp = min_value(board, INT_MIN, INT_MAX, j, 1, new_game);  // call the min for all positions.
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
    }

    else
    {
        for(int j=0; j<limit; j++)
        {
            if(board[block2-1][j] == '-')
            {
                board[block2-1][j] = 'x';
                temp = min_value(board, INT_MIN, INT_MAX, j, 1, new_game);  // call the min function.
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
            cout << "\t\t\t   The bot has to play in block " << block2 << endl;

        if(!check)                                                      // If all the positions are filled then 
                                                                        // the player can move anywhere.
        {
            cout << "\t\t\t   The bot can play anywhere" << endl;
            for(int i=0; i<limit; i++)
            {
                for(int j=0; j<limit; j++)
                {
                    if(board[i][j] == '-')
                    {
                        board[i][j] = 'x';
                        temp = min_value(board, INT_MIN, INT_MAX, j, 1, new_game);
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
    }
    return result (block, cell);                     // Return the move that is most fruitful.    
}

int max_value (vector<vector<char> > board, int alpha, int beta, int block, int depth, bool new_game)
{
    bool check = false;
    if(new_game)                                        // Estimate the utility value.
    {
        if(depth == max_depth-1)
            return utility (board);   
    }                          
    else if(depth == max_depth)
        return utility (board);

    int value = INT_MIN;

    for(int j=0; j<limit; j++)
    {
        if(board[block][j] == '-')
        {
            board[block][j] = 'x';
            value = max(value, min_value(board, alpha, beta, j, depth+1, new_game));  // call the min function.    
            board[block][j] = '-';
            check = true;

            if(value >= beta)                                               // Pruning condition.
                return value;
                
            alpha = max(alpha, value);
        }
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
                    value = max(value, min_value(board, alpha, beta, j, depth+1, new_game));
                    board[i][j] = '-';


                    if(value >= beta)
                        return value;

                    alpha = max(alpha, value);
                }
               
            }
        }
    }
    return value;
} 

int min_value (vector<vector<char> > board, int alpha, int beta, int block, int depth, bool new_game)
{
    bool check = false;
    if(new_game)                                        // Estimate the utility value.
    {
        if(depth == max_depth-1)
            return utility (board);      
    }                        
    else if(depth == max_depth)
        return utility (board);        

    int value = INT_MAX;

    for(int j=0; j<limit; j++)
    {
        if(board[block][j] == '-')
        {
            board[block][j] = 'o';
            value = min(value, max_value(board, alpha, beta, j, depth+1, new_game));  // Call the max function
            board[block][j] = '-';
            check = true;

            if(value <=alpha)                                               // Pruning condition.
            {
                return value;
            }
            beta = min(beta, value);
        }
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
                    value = min(value, max_value(board, alpha, beta, j, depth+1, new_game));  // Call the max function.
                    board[i][j] = '-';

                    if(value <=alpha)                           // Pruning function.
                    {
                        return value;
                    }
                    beta = min(beta, value);
                }
            }
        }
    }

    return value;
}
