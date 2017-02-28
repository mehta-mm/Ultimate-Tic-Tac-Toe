#include <iostream>
#include <vector>
#include <climits>
#pragma once	

using namespace std;

#define limit 9
#define LARGE_MAX  1000
#define LARGE_MIN -1000

int max_depth = 4;
int util_max = 0;
int util_min = 0;
bool chance = true;
bool new_game = true; 

int min_value(vector<vector<char> >, int, int, int, int);
int max_value(vector<vector<char> >, int, int, int, int);
void print_board(vector<vector<char> >);

class properties
{
public:
    properties();
    int utility_value;
    int potential_o;
    int potential_x;
    int simple_difference;
    char winner;
};

class result
{
    public:
    int block;
    int cell;
    result(int a, int b)
    {
        block = a;
        cell = b;
    }
};

properties::properties()
{
    utility_value = 0;
    potential_o = 0;
    potential_x = 0;
    simple_difference = 0;
    winner = '-';
}

result ans (0, 0);
