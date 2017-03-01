#include <iostream>
#include <vector>
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

    cout << endl;
    cout << "__________________________________________________" << endl << endl;
    cout << "Ultimate Tic Tac Toe By - Mohit Mehta and Annuay J" << endl;
    cout << "__________________________________________________" << endl;

    cout << endl << endl;
    cout << "Some points:" << endl;
    cout << "1) You are playing with o." << endl;
    cout << "2) Blocks and Cells are from 1 to 9. " << endl;
    cout << "3) The bot will play first. " << endl;
    cout << endl << endl;

    while(1)
    {
        if(chance)
        {
            if(find_winner (final_winner) == 'o')
            {
                cout << "Congratulations, You have won the game!!" << endl;
                break;
            }

            timestamp_t t0 = get_timestamp();                           // Start of the clock.
            ans = alpha_beta(board, next_block);                        // Call the alpha beta minimax function.
            board[ans.block][ans.cell] = 'x';
            timestamp_t t1 = get_timestamp();                           // Stop of the clock.


            cout << endl << "\t\t\t\t  Current board state: " << endl << endl;
            print_board(board);                                         // Print the board so that next player
                                                                        // can know the state of the board.
            for(int i=0; i<limit; i++)
            {
                if(final_winner[i] == '-')
                        final_winner[i] = find_winner(board[i]);
            }

            cout << "\t\t\t\t     Current Winners: " << endl << endl;
            print_char_vector (final_winner);
            cout << endl;

            next = ans.cell;

            cout << "\t\t\t   It took the bot ";
            cout << (t1-t0)/1000000.0L;
            cout << " sec to play the move." << endl;    
            chance = false;
        }

        else
        {
            if(find_winner(final_winner) == 'x')
            {
                cout << endl;
                cout << "\t\t\t   The bot has won the game" << endl;
                break;
            }

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
                cout << "\t\t\t   Your turn . You are to play in block: " << ans.cell+1 <<endl;
                cout << "\t\t\t   Format: <Cell No.> " <<endl;     // Take next move from the user.

                while(1)
                {
                    cout << "\t\t\t   ";
                    cin>>cell;
                    if(cell<1 || cell>9 || board[next][cell-1] != '-')                // Validation
                        cout << "\t\t\t\t   The input is wrong" << endl;
                    else
                    {
                        board[next][cell-1] = 'o';
                        break;
                    }
                }
            }

            else
            {
                cout << "\t\t\t\t   You can play anywhere on the board" << endl;
                cout << "\t\t\t\t   Format : <Block No.> <Cell No.>" << endl;               // Take next move from the user.
                while(1)
                {
                    cout << "\t\t\t   ";
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

            for(int i=0; i<limit; i++)
            {
                if(final_winner[i] == '-')
                    final_winner[i] = find_winner(board[i]);                
            }

            next_block = cell;
            chance = true;
            check = false;
        }
    }
}
