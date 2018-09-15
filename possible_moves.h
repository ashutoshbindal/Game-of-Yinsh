#ifndef POSSIBLE_MOVES
#define	POSSIBLE_MOVES

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