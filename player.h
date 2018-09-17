#ifndef PLAYER_H
#define	PLAYER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void split(string, string, vector<string>&);


extern int move_num;
extern int number_ring_self;
extern int number_ring_opponent;
extern int ring_self[5][2];
extern int ring_opponent[5][2];

extern vector<pair<int, int> > marker_self;
extern vector<pair<int, int> > marker_opponent;

void initialize_player();

void update_opponent(string);
void update_self(string);
void undo_update_opponent(string);
void undo_update_self(string);

void add_marker_self(int, int);
void add_marker_opponent(int, int);
void place_ring_self(int, int);
void place_ring_opponent(int, int);
void ring_remove_self(int, int);
void ring_remove_opponent(int, int);
void ring_add_self(int, int);
void ring_add_opponent(int, int);
void ring_update_self(int, int, int, int);
void ring_update_opponent(int, int, int, int);

void switch_marker(int, int, int, int);
void remove_marker(int, int, int, int);
void remove_single_marker(int, int);
void add_multiple_marker_self(int, int, int, int);
void add_multiple_marker_opponent(int, int, int, int);

vector<pair<int, int> > switch_marker_return(int, int, int, int);

string marker_5(pair<int, int>, int, pair<int, int>);
int exist_ring(int, int);
// int eval_func();
string get_move();


#endif
