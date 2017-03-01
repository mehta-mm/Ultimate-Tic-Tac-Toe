#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include "header.h"
#include "print_function.h"

#pragma once

using namespace std;

map<vector<char>, properties> small_board_hash;

void print_char_vector(vector<char> s)
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(j==0)
                cout << "\t\t\t\t\t  ";
            else 
                cout << " ";
            cout << s[(i*3)+j];
        } 
        cout << endl;      
    }
        
}


void print_map(map<vector<char>, properties> hashmap)
{
    map<vector<char>, properties> :: iterator it;
    
    for(it = hashmap.begin(); it!= hashmap.end(); it++)
    {
        vector<char> key = it->first;
        properties value = it->second;
        print_char_vector(key);
        cout<<" "<<value.winner;
        cout<<" "<<value.potential_x;
        cout<<" "<<value.potential_o;
        cout<<" "<<value.simple_difference;
        cout<<" "<<value.utility_value<<endl;
    }
}

char find_winner(vector<char> small_board)
{
    vector<char> bs = small_board;
    char winner = '-';

    //Row-wise conditions
    if      ((bs[0] == bs[1] && bs[1] == bs[2] && bs[1]!='-')) winner = bs[1];
    else if ((bs[3] == bs[4] && bs[4] == bs[5] && bs[4]!='-')) winner = bs[4];
    else if ((bs[6] == bs[7] && bs[7] == bs[8] && bs[7]!='-')) winner = bs[7];

    //Column-wise conditions
    else if ((bs[0] == bs[3] && bs[3] == bs[6] && bs[3]!='-')) winner = bs[3];
    else if ((bs[1] == bs[4] && bs[4] == bs[7] && bs[4]!='-')) winner = bs[4];
    else if ((bs[2] == bs[5] && bs[5] == bs[8] && bs[5]!='-')) winner = bs[5];    

    //Diagonal conditions
    else if ((bs[0] == bs[4] && bs[4] == bs[8] && bs[4]!='-')) winner = bs[4];
    else if ((bs[2] == bs[4] && bs[4] == bs[6] && bs[4]!='-')) winner = bs[4];    

    return winner;
}


int count(vector<char> v, char symbol)
{
    int val = 0;
    for(int i=0; i<3; i++)
    {
        if(v[i] == symbol) 
            val++;
    }
    return val;
}


int potential_count(vector<char> bs, char symbol)
{
    int t = 0, r = 0, potential = 0;
    vector<vector<char> > v;
    vector<char> temp;   

    temp.push_back(bs[0]);
    temp.push_back(bs[1]);
    temp.push_back(bs[2]);
    
    v.push_back(temp); 
    temp.clear();

    temp.push_back(bs[3]);
    temp.push_back(bs[4]);
    temp.push_back(bs[5]);

    v.push_back(temp); 
    temp.clear();

    temp.push_back(bs[6]);
    temp.push_back(bs[7]);
    temp.push_back(bs[8]);

    v.push_back(temp); 
    temp.clear();

    temp.push_back(bs[0]);
    temp.push_back(bs[3]);
    temp.push_back(bs[6]);

    v.push_back(temp); 
    temp.clear();

    temp.push_back(bs[1]);
    temp.push_back(bs[4]);
    temp.push_back(bs[7]);  

    v.push_back(temp);
    temp.clear();

    temp.push_back(bs[2]);
    temp.push_back(bs[5]);
    temp.push_back(bs[8]);    

    v.push_back(temp); 
    temp.clear();

    temp.push_back(bs[0]);
    temp.push_back(bs[4]);
    temp.push_back(bs[8]);    

    v.push_back(temp);
    temp.clear();

    temp.push_back(bs[2]);
    temp.push_back(bs[4]);
    temp.push_back(bs[6]);    

    v.push_back(temp);
    temp.clear();

    for(int i = 0; i != v.size(); i++)
    {
        t = count(v[i], symbol);
        r = count(v[i], '-');
        if(t==2 && r==1) 
            potential++;
    }
    return potential;
}


int simple_difference(vector<char> bs)
{
    int o_count = 0, x_count = 0;
    for(int i=0; i<bs.size(); i++)
    {
        if (bs[i] == 'o') 
            o_count++;
        if (bs[i] == 'x') 
            x_count++;
    }
    return x_count - o_count;
}


properties small_board_utility(vector<char> bs)
{
    properties current;
    if(find_winner(bs) == 'x') //bot wins small board
    {
        current.utility_value = 40;
        current.winner = 'x';
    }

    else if (find_winner(bs) == 'o') //human wins small board
    {
        current.utility_value = -40;
        current.winner = 'o';
    }

    else
    {
        current.winner = '-';
        int util = 0;

        if (bs[4] == 'x')           //bot occupies centre square of small board
            util +=  8; 

        if (bs[4] == 'o')           //human occupies centre square of small board
            util += -8; 

        current.potential_x = potential_count(bs, 'x');
        util += current.potential_x *  4;  //potential ways for bot to win * 2

        current.potential_o = potential_count(bs, 'o');
        util += current.potential_o * -4;  //potential ways for human to win * 2

        current.simple_difference =  simple_difference(bs); //number of 'x' - number of 'o'
        util += current.simple_difference;

        current.utility_value = util;
    }

    return current;
}


void generate_and_hash(vector<char> s, vector<char> prefix, int n, int k)
{
    if(k==0)
    {
        small_board_hash[prefix] = small_board_utility(prefix);
        return;
    }

    for(int i=0; i<n; i++)
    {
        vector<char> new_prefix = prefix;
        new_prefix.push_back(s[i]);
        generate_and_hash(s, new_prefix, n, k-1);
    }
}


void hash_wrapper()
{
    vector<char> s, prefix;
    s.push_back('x');
    s.push_back('o');
    s.push_back('-');
    int n = s.size();
    generate_and_hash(s, prefix, n, 9);
}


int utility(vector<vector<char> > state)
{   
    vector<properties> winner_properties;
    vector<char> winners;    

    for(int i=0; i<state.size(); i++)
    {
        winner_properties.push_back(small_board_hash[state[i]]);
        winners.push_back(winner_properties[i].winner);
    }
    
    properties p = small_board_hash[winners];

    int param_winner = p.winner;            //Who won the big board?   

    if(p.winner == 'x')
        return LARGE_MAX;

    else if(p.winner == 'o')
        return LARGE_MIN;

    else
    {
        int util = 0;

        for(int i=0; i<winner_properties.size(); i++)   //Sum of utility of all small boards
            util += winner_properties[i].utility_value;

        util += p.potential_x *  40;  //x potential in big board added
        util += p.potential_o * -40;  //o potential in big board added

        if(winners[4] == 'x') 
            util +=  120;   //if bot holds centre square of main board
        if(winners[4] == 'o') 
            util += -120;   //if human holds centre square of main board

        //Corner boards occupied by bot
        if(winners[0] == 'x')
            util += 40;

        if(winners[2] == 'x')
            util += 40;

        if(winners[6] == 'x')
            util += 40;

        if(winners[8] == 'x')
            util += 40;

        //Corner boards occupied by human
        if(winners[0] == 'o')
            util -= 40;

        if(winners[2] == 'o')
            util -= 40;   

        if(winners[6] == 'o')
            util -= 40;

        if(winners[8] == 'o')
            util -= 40;

        return util;
    }
}
