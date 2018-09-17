#ifndef POSSIBLE_MOVES_H
#define	POSSIBLE_MOVES_H

#include <iostream>
#include <map>
#include <vector>
#include "map.h"

using namespace std;

//ring bound stores the nearest ring positions first two along X axis movevement
//and then two Y and then two
//the values stores are last accessible values (means rings are places after these values)
extern cordinate2 ring_bound[6];

//bound_x stores the minium and maximum value of y, z for any x.
//sequence: min_y, min_z, max_y, max_z
//similarly bound_y (x, then z), bound_z (x, then y)

extern int bound_x[11][4];
extern int bound_y[11][4];
extern int bound_z[11][4];

void place_bounds();
void bound_ring(int, int, int);
void bound_marker(int, int, int);
// bool exist_marker(int, int, int);
vector<cordinate2> give_positions(int, int, int);

void update_board_score(int, int, int);

int total_score();

pair<vector<pair<cordinate2, cordinate2> >, vector<pair<cordinate2, cordinate2> > > check_5(int, int, int);

pair<pair<int, int>, pair<int, int> > select_5(pair<cordinate2, cordinate2>);

#endif