#ifndef PLAYER_H
#define	PLAYER_H

#include <iostream>

using namespace std;

class player{
	public:
		int number_ring_self;
		int number_ring_opponent;
		int ring_self[5][2];
		int ring_opponent[5][2];

		vector<pair<int, int>> marker_self;
		vector<pair<int, int>> marker_opponent;

		void update_opponent(string);
		void update_self(string);
		void add_marker_self(int, int);
		void add_marker_opponent(int, int);
		void ring_mine(int, int);
		void ring_opponent(int, int);
		void ring_remove_mine(int, int);
		void ring_remove_opponent(int, int);
		void ring_update_mine(int, int, int, int);
		void ring_update_opponent(int, int, int, int);
		int eval_func();
		string get_move();
}

#endif
