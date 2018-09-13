#ifndef MAP_H
#define	MAP_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct cordinate2
{
	int x;
	int y;
	int z;
};

extern map<pair<int, int>, cordinate2> hex2cart;
extern pair<int, int> cart2hex[11][11][11];

vector<pair<int, int> > places(int, int, int, int);

void initialize();

#endif
