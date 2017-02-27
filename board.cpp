#include <iostream>
#include <vector>
#include <ctime>
#include "print_function.h"
#include "alpha_beta.h"
#include "header.h"
#include "utility.h"

using namespace std;

int main()
{
    hash_wrapper();
    bool check = false;
    vector<vector<char> > board(9, vector<char>(9, '-'));               // Initiate the board.
    int block, cell, next = 0;
    int next_block = 0;

    cout<< "You are playing with o." << endl << "Blocks are from 1 to 9" << endl;;

    while(1)
    {
        if(chance)
        {
            if(utility(board) == -1000)
                break;

            cout << "It's bot's turn." << endl;

            int start_s = clock();                                      // Start of the clock.
            ans = alpha_beta(board, next_block);                        // Call the alpha beta minimax function.
            board[ans.block][ans.cell] = 'x'; 
            int stop_s = clock();                                       // Stop of the clock.

            print_board(board);                                         // Print the board so that next player
                                                                        // can know the state of the board.
            next = ans.cell;

            cout << "It took the bot " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
            cout << " sec to play the move." << endl;
            chance = !chance;
        }

        else
        {
            if(utility(board) == 1000)
                break;

            for (int i=0; i<limit; i++)
            {
                if(board[next][i] == '-')
                {
                    check = true;                                       //If any of the cell in the next block is not empty
                                                                        // then the player can play anywhere on the board.
                }
            }

            if(check)
            {
                cout << "Your turn. You are to play in block: " << ans.cell+1 <<endl;     // Take next move from the user.

                while(1)
                {
                    cin>>cell;
                    if(cell<1 || cell>9 || board[next][cell-1] != '-')                // Validation
                        cout << "The input is wrong" << endl;
                    else
                    {
                        board[next][cell-1] = 'o';
                        break;
                    }
                }
            }

            else
            {
                cout << "You can play anywhere on the board" << endl;               // Take next move from the user.
                while(1)
                {
                    cin>>block>>cell;
                    if(block<1 || block>9 || cell<1 || cell>9 || board[block-1][cell-1] != '-')     // Validation
                        cout << "The input is wrong" << endl;
                    else
                    {
                        board[block-1][cell-1] = 'o';            
                        break;
                    }
                }
            }
            next_block = cell;
            chance = !chance;
            check = false;
        }
    }

    if(chance)
        cout << "The bot has won!!" << endl;
    else
        cout << "You won!!" <<endl;
}
