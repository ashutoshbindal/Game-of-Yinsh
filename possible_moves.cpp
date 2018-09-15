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
int board_state1[11][11][11];

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
	bool flag= false;
	for(int i= y-1; i>= ring_bound[0].y; i--){
		j--;
		if(exist_x == 0 && board_state1[x][i][j]>= 0)	exist_x = 1;
		if(exist_x == 1 && board_state1[x][i][j]>= 0){
			ring_bound[0] = cordinate2 {x, i, j};
		}
	}
	exist_x = 0;
	j= z;
	for(int i= y+1; i<= ring_bound[1].y; i++){
		j++;
		if(exist_x == 0 && board_state1[x][i][j]>= 0)	exist_x = 1;
		if(exist_x == 1 && board_state1[x][i][j]>= 0){
			ring_bound[1] = cordinate2 {x, i, j};
		}
	}
	exist_x = 0;
	j= z;
	for(int i= x-1; i>= ring_bound[2].x; i--){
		j--;
		if(exist_x == 0 && board_state1[i][y][j]>= 0)	exist_x = 1;
		if(exist_x == 1 && board_state1[i][y][j]>= 0){
			ring_bound[2] = cordinate2 {i, y, j};
		}
	}
	exist_x = 0;
	j= z;
	for(int i= x+1; i<= ring_bound[3].x; i++){
		j++;
		if(exist_x == 0 && board_state1[i][y][j]>= 0)	exist_x = 1;
		if(exist_x == 1 && board_state1[i][y][j]>= 0){
			ring_bound[3] = cordinate2 {i, y, j};
		}
	}
	exist_x = 0;
	j= y;
	for(int i= x-1; i>= ring_bound[4].x; i--){
		j--;
		if(exist_x == 0 && board_state1[i][j][z]>= 0)	exist_x = 1;
		if(exist_x == 1 && board_state1[i][j][z]>= 0){
			ring_bound[4] = cordinate2 {i, j, z};
		}
	}
	exist_x = 0;
	j= y;
	for(int i= x+1; i<= ring_bound[5].x; i++){
		j++;
		if(exist_x == 0 && board_state1[i][j][z]>= 0)	exist_x = 1;
		if(exist_x == 1 && board_state1[i][j][z]>= 0){
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
		if(j!= y && k!= z && board_state1[x][j][k]== -1)	v.push_back(x, j, k);
	}
	k = ring_bound[2].z-1;
	for(i= ring_bound[2].x; i<= ring_bound[3].x; j++){
		k++;
		if(i!= x && k!= z && board_state1[i][y][k]== -1)	v.push_back(i, y, k);
	}
	i = ring_bound[4].x-1;
	for(j= ring_bound[4].y; j<= ring_bound[5].y; j++){
		i++;
		if(i!= x && k!= z && board_state1[i][j][z]== -1)	v.push_back(i, j, z);
	}
	return v;
}

void update_board_score(int x, int y, int z){
	int j, k, val_opponent, val_mine, cnt, score_temp;
	bool opponent_flag, mine_flag;
	mine_flag = false;
	opponent_flag = false;
	cnt = 0;
	val_mine= 0;
	val_opponent= 0;
	score_temp= 0;
	for(int j= bound_x[x][0]; j<= bound_x[x][2]; j++){
		k = bound_x[x][1]+ cnt;
		cnt++;
		if(board_state1[x][j][k]== 0){
			if(mine_flag){
				val_mine++;
			}
			else if(opponent_flag){
				opponent_flag = false;
				mine_flag = true;
				score_temp = score_temp - (val_opponent*val_opponent);
				val_opponent = 0;
			}
			else{
				mine_flag = true;
				opponent_flag = false;
				val_mine++;
			}
		}
		else if(board_state1[x][j][k]== 1){
			if(mine_flag){
				mine_flag = false;
				opponent_flag = true;
				score_temp = score_temp + (val_mine*val_mine);
				val_mine= 0;
			}
			else if(opponent_flag){
				val_opponent++;
			}
			else{
				mine_flag = false;
				opponent_flag
				val_opponent++;
			}
		}
		else{
			score_temp+= (val_mine*val_mine) - (val_opponent*val_opponent);
			val_opponent= 0;
			val_mine= 0;
			mine_flag= false;
			opponent_flag= false;
		}
	}
	score[x][0] = score_temp;

	mine_flag = false;
	opponent_flag = false;
	cnt = 0;
	val_mine= 0;
	val_opponent= 0;
	score_temp= 0;
	for(int i= bound_y[y][0]; i<= bound_y[y][2]; i++){
		k = bound_y[y][1]+ cnt;
		cnt++;
		if(board_state1[i][y][k]== 0){
			if(mine_flag){
				val_mine++;
			}
			else if(opponent_flag){
				opponent_flag = false;
				mine_flag = true;
				score_temp = score_temp - (val_opponent*val_opponent);
				val_opponent = 0;
			}
			else{
				mine_flag = true;
				opponent_flag = false;
				val_mine++;
			}
		}
		else if(board_state1[i][y][k]== 1){
			if(mine_flag){
				mine_flag = false;
				opponent_flag = true;
				score_temp = score_temp + (val_mine*val_mine);
				val_mine= 0;
			}
			else if(opponent_flag){
				val_opponent++;
			}
			else{
				mine_flag = false;
				opponent_flag
				val_opponent++;
			}
		}
		else{
			score_temp+= (val_mine*val_mine) - (val_opponent*val_opponent);
			val_opponent= 0;
			val_mine= 0;
			mine_flag= false;
			opponent_flag= false;
		}
	}
	score[y][1] = score_temp;

	mine_flag = false;
	opponent_flag = false;
	cnt = 0;
	val_mine= 0;
	val_opponent= 0;
	score_temp= 0;
	for(int i= bound_z[z][0]; i<= bound_z[z][2]; i++){
		j = bound_z[z][1]+ cnt;
		cnt++;
		if(board_state1[i][j][z]== 0){
			if(mine_flag){
				val_mine++;
			}
			else if(opponent_flag){
				opponent_flag = false;
				mine_flag = true;
				score_temp = score_temp - (val_opponent*val_opponent);
				val_opponent = 0;
			}
			else{
				mine_flag = true;
				opponent_flag = false;
				val_mine++;
			}
		}
		else if(board_state1[i][j][z]== 1){
			if(mine_flag){
				mine_flag = false;
				opponent_flag = true;
				score_temp = score_temp + (val_mine*val_mine);
				val_mine= 0;
			}
			else if(opponent_flag){
				val_opponent++;
			}
			else{
				mine_flag = false;
				opponent_flag
				val_opponent++;
			}
		}
		else{
			score_temp+= (val_mine*val_mine) - (val_opponent*val_opponent);
			val_opponent= 0;
			val_mine= 0;
			mine_flag= false;
			opponent_flag= false;
		}
	}
	score[z][2] = score_temp;
}

int total_score(){
	int val= 0;
	for(int i= 0; i< 11; i++){
		val+= score[i][0];
		val+= score[i][1];
		val+= score[i][2];
	}
	return val;
}

vector<pair<cordinate2, cordinate2>> check_5(int x, int y, int z){
	bool mine_flag= false, opponent_flag= false;
	int i, j, k, val_mine, val_opponent, cnt= 0;

	val_mine= 0;
	val_opponent= 0;
	cnt= 0;
	mine_flag= false;
	opponent_flag= false;
	vector<pair<cordinate2, cordinate2>> v;
	for(j= bound_x[x][0]; j< bound_x[x][2]; j++){
		k= bound_x[x][1]+cnt;
		cnt++;
		if(board_state1[x][j][k]== 0){
			if(mine_flag)	val_mine++;
			else if(opponent_flag){
				if(val_opponent== 5){
					//do something
				}
				opponent_flag= false;
				mine_flag= true;
				val_opponent= 0;
			}
			else{
				val_mine= 1;
				val_opponent= 0;
				mine_flag= true;
			}
		}
		if(board_state1[x][j][k]==1){
			if(mine_flag){
				if(val_mine==5){
					//do something
				}
				val_mine= 0;
				mine_flag= false;
				opponent_flag= false;
			}
			else if(opponent_flag)	opponent_flag++;
			else{

			}
		}
	}
}