#include <iostream>
#include <vector>
#include <map>

#include "player.h"
#include "map.h"
#include "possible_moves.h"

using namespace std;

int bound_x[11][4];
int bound_y[11][4];
int bound_z[11][4];

cordinate2 ring_bound[6];

void place_bounds(){
	int temp_x = {
		{6,1,9,4},
		{4,0,10,6},
		{3,0,10,7},
		{2,0,10,8},
		{1,0,10,9},
		{1,1,9,9},
		{0,1,9,10},
		{0,2,8,10},
		{0,3,7,10},
		{0,4,6,10},
		{1,6,4,9},	
	}
	bound_x = temp_x;
	int temp_y = {
		{6,1,9,4},
		{4,0,10,6},
		{3,0,10,7},
		{2,0,10,8},
		{1,0,10,9},
		{1,1,9,5},
		{0,1,9,10},
		{0,2,8,10},
		{0,3,7,10},
		{0,4,6,10},
		{1,6,4,9},
	}
	bound_y = temp_y;
	int temp_z = {
		{1,4,4,1},
		{0,6,6,0},
		{0,7,7,0},
		{0,8,8,0},
		{0,9,9,0},
		{0,9,9,1},
		{1,10,10,1},
		{2,10,10,2},
		{3,10,10,3},
		{4,10,10,4},
		{6,9,9,6},	
	}
	bound_z = temp_z;
}

// map<pair<int, int>, cordinate2> hex2cart;
// pair<int, int> cart2hex[11][11][11];
// vector<marker> board_state[11][3];

void bound_ring(int x, int y, int z){	
	ring_bound[0] = cordinate2 {x, bound_x[x][0], bound_x[x][1]};	//lower x
	ring_bound[1] = cordinate2 {x, bound_x[x][2], bound_x[x][3]};	//upper x
	ring_bound[2] = cordinate2 {bound_y[y][0], y, bound_y[y][1]};	//lower y
	ring_bound[3] = cordinate2 {bound_y[y][2], y, bound_y[y][3]};	//upper y
	ring_bound[4] = cordinate2 {bound_z[z][0], bound_z[z][1], z};	//lower z
	ring_bound[5] = cordinate2 {bound_z[z][2], bound_z[z][3], z};	//upper z

	for(int P= 0; P< 2; P++){
		for(int i= 0; i< 5; i++){
			if (P== 0){
				temp = hex2cart[pair<int, int>(ring_self[i][0], ring_self[i][1])];	
			}
			else{
				temp = hex2cart[pair<int, int>(ring_opponent[i][0], ring_opponent[i][1])];		
			}
			if(temp.x == x){
				//this ring lies on the same x
				if(temp.y < y && ring_bound[0].y<= temp.y){
					ring_bound[0] = cordinate2 {x, temp.y+1, temp.z+1};
				}
				if(temp.y > y && ring_bound[1].y>= temp.y){
					ring_bound[1] = cordinate2 {x, temp.y-1, temp.z-1};
				}

			}
			else if(temp.y == y){
				//this ring lies on the same x
				if(temp.x < x && ring_bound[2].x<= temp.x){
					ring_bound[2] = cordinate2 {temp.x+1, y, temp.z+1};
				}
				if(temp.x > x && ring_bound[3].x>= temp.x){
					ring_bound[3] = cordinate2 {temp.x-1, y, temp.z-1};
				}

			}
			else if(temp.z == z){
				//this ring lies on the same x
				if(temp.z < z && ring_bound[4].y<= temp.y){
					ring_bound[4] = cordinate2 {temp.x+1, temp.y+1, z};
				}
				if(temp.z > z && ring_bound[1].y>= temp.y){
					ring_bound[5] = cordinate2 {temp.x, temp.y-1, z};
				}

			}
		}		
	}
}

bool exist_marker(int x, int y, int z){
	for(int i= 0; i< board_state[x].size(); i++){
		if(board_state[x][i].x == y)	return true;
	}
	return false;
}

void bound_marker(int x, int y, int z){
	int exist_x = 0, j= z;
	for(int i= y-1; i>= ring_bound[0].y; i--){
		j--;
		if(exist_x == 0 && exist_marker(x, i, j))	exist_x = 1;
		if(exist_x == 1 && exist_marker(x, i, j)){
			ring_bound[0] = cordinate2 {x, i, j};
		}
	}
	exist_x = 0;
	j= z;
	for(int i= y+1; i<= ring_bound[1].y; i++){
		j++;
		if(exist_x == 0 && exist_marker(x, i, j))	exist_x = 1;
		if(exist_x == 1 && exist_marker(x, i, j)){
			ring_bound[1] = cordinate2 {x, i, j};
		}
	}
	exist_x = 0;
	j= z;
	for(int i= x-1; i>= ring_bound[2].x; i--){
		j--;
		if(exist_x == 0 && exist_marker(i, y, j))	exist_x = 1;
		if(exist_x == 1 && exist_marker(i, y, j)){
			ring_bound[2] = cordinate2 {i, y, j};
		}
	}
	exist_x = 0;
	j= z;
	for(int i= x+1; i<= ring_bound[3].x; i++){
		j++;
		if(exist_x == 0 && exist_marker(i, y, j))	exist_x = 1;
		if(exist_x == 1 && exist_marker(i, y, j)){
			ring_bound[3] = cordinate2 {i, y, j};
		}
	}
	exist_x = 0;
	j= y;
	for(int i= x-1; i>= ring_bound[4].x; i--){
		j--;
		if(exist_x == 0 && exist_marker(i, j, z))	exist_x = 1;
		if(exist_x == 1 && exist_marker(i, j, z)){
			ring_bound[4] = cordinate2 {i, j, z};
		}
	}
	exist_x = 0;
	j= y;
	for(int i= x+1; i<= ring_bound[5].x; i++){
		j++;
		if(exist_x == 0 && exist_marker(i, j, z))	exist_x = 1;
		if(exist_x == 1 && exist_marker(i, j, z)){
			ring_bound[5] = cordinate2 {i, j, z};
		}
	}
}

vector<cordinate2> give_positions(int x, int y, int z){
	bound_ring(x, y, z);
	bound_marker(x, y, z);
	vector<cordinate2> v;
	int i, j, k;
	i= x;
	k = ring_bound[0].z-1;
	for(j= ring_bound[0].y; j<= ring_bound[1].y; j++){
		k++;
		if(j!= y && k!= z)	v.push_back(x, j, k);
	}
	k = ring_bound[2].z-1;
	for(i= ring_bound[2].x; i<= ring_bound[3].x; j++){
		k++;
		if(i!= x && k!= z)	v.push_back(i, y, k);
	}
	i = ring_bound[4].x-1;
	for(j= ring_bound[4].y; j<= ring_bound[5].y; j++){
		i++;
		if(i!= x && k!= z)	v.push_back(i, j, z);
	}
	return v;
}