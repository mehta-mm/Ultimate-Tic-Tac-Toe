#include <iostream>
#include <vector>
#include <climits>
#include <sys/time.h>
#pragma once	

using namespace std;

#define limit 9
#define LARGE_MAX  1000
#define LARGE_MIN -1000

typedef unsigned long long timestamp_t;

int max_depth = 6;
int util_max = 0;
int util_min = 0;
bool chance = true;
bool new_game = true; 

int min_value(vector<vector<char> >, int, int, int, int, bool);
int max_value(vector<vector<char> >, int, int, int, int, bool);
void print_board(vector<vector<char> >);

vector<char> final_winner (9, '-');

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
result ans (0, 0);

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

properties::properties()
{
    utility_value = 0;
    potential_o = 0;
    potential_x = 0;
    simple_difference = 0;
    winner = '-';
}

static timestamp_t get_timestamp ()
{
  struct timeval now;
  gettimeofday (&now, NULL);
  return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}
