#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <limits.h>
#include <algorithm>

#include "player.h"
#include "map.h"
#include "possible_moves.h"

using namespace std;

int move_num;
int number_ring_self;
int number_ring_opponent;
int ring_self[5][2];
int ring_opponent[5][2];

//use it as: split(string, char_to_split, vector_string)
void split(string str, string splitBy, vector<string>& tokens)
{
    tokens.push_back(str);
    size_t splitAt;
    size_t splitLen = splitBy.size();
    string frag;
    while(true)
    {
        frag = tokens.back();
        splitAt = frag.find(splitBy);
        if(splitAt == string::npos)
        {
            break;
        }
        tokens.back() = frag.substr(0, splitAt);
        tokens.push_back(frag.substr(splitAt+splitLen, frag.size()-(splitAt+splitLen)));
    }
}

void initialize_player(){
	number_ring_self = 0;
	number_ring_opponent = 0;
    move_num = 0;

	//Initialize for all the ring position to -1
	for(int i=0; i<5; i++)
	{
		ring_self[i][0] = -1;
		ring_self[i][1] = -1;
		ring_opponent[i][0] = -1;
		ring_opponent[i][1] = -1;
	}
}

// int eval_func(){
//
//     //write the code for the alpha-beta pruning
//
//     int s;
// 	return s;
// }

void update_self(string move){
	vector<string> segment;
	split(move, " ", segment);

	if (segment[0] == "P"){
		//Place your ring
		place_ring_self(stoi(segment[1]), stoi(segment[2]));
	}
	else if (segment[0] == "S"){
		if(segment.size() == 6){
			ring_update_self(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));
			//marker update on the old ring position
			add_marker_self(stoi(segment[1]), stoi(segment[2]));

			//switch the color of the markers in between
            switch_marker(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));
		}
		else if(segment.size() == 15){
			ring_update_self(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));
			//marker update on the old ring position
			add_marker_self(stoi(segment[1]), stoi(segment[2]));

			//switch the color of the markers in between
            switch_marker(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));

			//remove the markers from RS to RE
            remove_marker(stoi(segment[7]), stoi(segment[8]), stoi(segment[10]), stoi(segment[11]));

			ring_remove_self(stoi(segment[13]), stoi(segment[14]));
		}
	}
    else if(segment[0] == "RS"){
        //remove the markers from RS to RE
        remove_marker(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));

        ring_remove_self(stoi(segment[7]), stoi(segment[8]));
    }
	else {

	}
}

void update_opponent(string move){
	vector<string> segment;
	split(move, " ", segment);

	if (segment[0] == "P"){
		//Place your ring
		place_ring_opponent(stoi(segment[1]), stoi(segment[2]));
	}
	else if (segment[0] == "S"){
		if(segment.size() == 6){
			ring_update_opponent(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));
			//marker update on the old ring position
			add_marker_opponent(stoi(segment[1]), stoi(segment[2]));

			//switch the color of the markers in between
            switch_marker(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));
		}
		else if(segment.size() == 15){
			ring_update_opponent(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));
			//marker update on the old ring position
			add_marker_opponent(stoi(segment[1]), stoi(segment[2]));

			//switch the color of the markers in between
            switch_marker(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));

			//remove the markers from RS to RE
            remove_marker(stoi(segment[7]), stoi(segment[8]), stoi(segment[10]), stoi(segment[11]));

			ring_remove_opponent(stoi(segment[13]), stoi(segment[14]));
		}
	}
    else if(segment[0] == "RS"){
        //remove the markers from RS to RE
        remove_marker(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));

        ring_remove_opponent(stoi(segment[7]), stoi(segment[8]));
    }
	else{

	}
}

void place_ring_self(int hex, int pos){
	number_ring_self++;
	ring_self[number_ring_self-1][0] = hex;
	ring_self[number_ring_self-1][1] = pos;
}

void place_ring_opponent(int hex, int pos){
	number_ring_opponent++;
	ring_opponent[number_ring_opponent-1][0] = hex;
	ring_opponent[number_ring_opponent-1][1] = pos;
}

void ring_update_self(int old_hex, int old_pos, int new_hex, int new_pos){
	for(int i=0; i<5; i++){
		if(ring_self[i][0] == old_hex && ring_self[i][1] == old_pos){
			ring_self[i][0] = new_hex;
			ring_self[i][1] = new_pos;
			break;
		}
	}
}

void ring_update_opponent(int old_hex, int old_pos, int new_hex, int new_pos){
	for(int i=0; i<5; i++){
		if(ring_opponent[i][0] == old_hex && ring_opponent[i][1] == old_pos){
			ring_opponent[i][0] = new_hex;
			ring_opponent[i][1] = new_pos;
			break;
		}
	}
}

void ring_remove_self(int hex, int pos){
	for(int i=0; i<5; i++){
		if(ring_self[i][0] == hex && ring_self[i][1] == pos){
			ring_self[i][0] = -1;
			ring_self[i][1] = -1;
			number_ring_self--;
			break;
 		}
	}
}

void ring_remove_opponent(int hex, int pos){
	for(int i=0; i<5; i++){
		if(ring_opponent[i][0] == hex && ring_opponent[i][1] == pos){
			ring_opponent[i][0] = -1;
			ring_opponent[i][1] = -1;
			number_ring_opponent--;
			break;
		}
	}
}

void add_marker_self(int hex, int pos){
	marker_self.push_back(pair<int, int>(hex, pos));

    //adding the marker to board_state
    cordinate2 temp_marker = hex2cart[pair<int, int>(hex, pos)];
    board_state1[temp_marker.x][temp_marker.y][temp_marker.z] = 1;
    // marker m1 (temp_marker.y, temp_marker.z, true);
    // marker m2 (temp_marker.z, temp_marker.x, true);
    // marker m3 (temp_marker.x, temp_marker.y, true);
    // board_state[temp_marker.x][0].push_back(m1);
    // board_state[temp_marker.y][1].push_back(m2);
    // board_state[temp_marker.z][2].push_back(m3);

    //update board score
    update_board_score(temp_marker.x, temp_marker.y, temp_marker.z);
}

void add_marker_opponent(int hex, int pos){
	marker_opponent.push_back(pair<int, int>(hex, pos));

    //adding the marker to board_state
    cordinate2 temp_marker = hex2cart[pair<int, int>(hex, pos)];
    board_state1[temp_marker.x][temp_marker.y][temp_marker.z] = 0;
    // marker m1 (temp_marker.y, temp_marker.z, false);
    // marker m2 (temp_marker.z, temp_marker.x, false);
    // marker m3 (temp_marker.x, temp_marker.y, false);
    // board_state[temp_marker.x][0].push_back(m1);
    // board_state[temp_marker.y][1].push_back(m2);
    // board_state[temp_marker.z][2].push_back(m3);

    //update_board_score
    update_board_score(temp_marker.x, temp_marker.y, temp_marker.z);
}

void switch_marker(int hex1, int pos1, int hex2, int pos2){
    vector<pair<int, int> > mark = places(hex1, pos1, hex2, pos2);

    for(int i=0; i<mark.size(); i++)
    {
        if( find(marker_self.begin(), marker_self.end(), mark[i]) != marker_self.end() ){
            marker_self.erase(remove(marker_self.begin(), marker_self.end(), mark[i]), marker_self.end());
            marker_opponent.push_back(mark[i]);
        }
        else if( find(marker_opponent.begin(), marker_opponent.end(), mark[i]) != marker_opponent.end() ){
            marker_opponent.erase(remove(marker_opponent.begin(), marker_opponent.end(), mark[i]), marker_opponent.end());
            marker_self.push_back(mark[i]);
        }
    }

    //switching the markers on the board_state1
    for(int i=0; i<mark.size(); i++){
        pair<int, int> temp_hex = mark[i];
        cordinate2 temp = hex2cart[temp_hex];

        //checking along each axis for the marker and flipping
        if(board_state1[temp.x][temp.y][temp.z] == 0){
            board_state1[temp.x][temp.y][temp.z] = 1;
        }
        else if(board_state1[temp.x][temp.y][temp.z] == 1){
            board_state1[temp.x][temp.y][temp.z] = 0;
        }
        // vector<marker> board_x = board_state[temp.x][0];
        // for(int j=0; j<board_x.size(); j++){
        //     if(board_x[j].x == temp.y && board_x[j].y == temp.z){
        //         board_x[j].token ^= true;
        //         board_state[temp.x][0] = board_x;
        //         break;
        //     }
        // }
        // vector<marker> board_y = board_state[temp.y][1];
        // for(int j=0; j<board_y.size(); j++){
        //     if(board_y[j].x == temp.z && board_y[j].y == temp.x){
        //         board_y[j].token ^= true;
        //         board_state[temp.y][1] = board_y;
        //         break;
        //     }
        // }
        // vector<marker> board_z = board_state[temp.z][2];
        // for(int j=0; j<board_z.size(); j++){
        //     if(board_z[j].x == temp.x && board_z[j].y == temp.y){
        //         board_z[j].token ^= true;
        //         board_state[temp.z][2] = board_z;
        //         break;
        //     }
        // }
    }

    //update board score
    for(int i=0; i<mark.size(); i++){
        pair<int, int> temp_hex = mark[i];
        cordinate2 temp = hex2cart[temp_hex];

        if(board_state1[temp.x][temp.y][temp.z] != -1){
            update_board_score(temp.x, temp.y, temp.z);
        }
    }
}

vector<pair<int, int> > switch_marker_return(int hex1, int pos1, int hex2, int pos2){
    vector<pair<int, int> > mark = places(hex1, pos1, hex2, pos2);

    for(int i=0; i<mark.size(); i++)
    {
        if( find(marker_self.begin(), marker_self.end(), mark[i]) != marker_self.end() ){
            marker_self.erase(remove(marker_self.begin(), marker_self.end(), mark[i]), marker_self.end());
            marker_opponent.push_back(mark[i]);
        }
        else if( find(marker_opponent.begin(), marker_opponent.end(), mark[i]) != marker_opponent.end() ){
            marker_opponent.erase(remove(marker_opponent.begin(), marker_opponent.end(), mark[i]), marker_opponent.end());
            marker_self.push_back(mark[i]);
        }
    }

    //switching the markers on the board_state1
    for(int i=0; i<mark.size(); i++){
        pair<int, int> temp_hex = mark[i];
        cordinate2 temp = hex2cart[temp_hex];

        //checking along each axis for the marker and flipping
        if(board_state1[temp.x][temp.y][temp.z] == 0){
            board_state1[temp.x][temp.y][temp.z] = 1;
        }
        else if(board_state1[temp.x][temp.y][temp.z] == 1){
            board_state1[temp.x][temp.y][temp.z] = 0;
        }
        // vector<marker> board_x = board_state[temp.x][0];
        // for(int j=0; j<board_x.size(); j++){
        //     if(board_x[j].x == temp.y && board_x[j].y == temp.z){
        //         board_x[j].token ^= true;
        //         board_state[temp.x][0] = board_x;
        //         break;
        //     }
        // }
        // vector<marker> board_y = board_state[temp.y][1];
        // for(int j=0; j<board_y.size(); j++){
        //     if(board_y[j].x == temp.z && board_y[j].y == temp.x){
        //         board_y[j].token ^= true;
        //         board_state[temp.y][1] = board_y;
        //         break;
        //     }
        // }
        // vector<marker> board_z = board_state[temp.z][2];
        // for(int j=0; j<board_z.size(); j++){
        //     if(board_z[j].x == temp.x && board_z[j].y == temp.y){
        //         board_z[j].token ^= true;
        //         board_state[temp.z][2] = board_z;
        //         break;
        //     }
        // }
    }
    //update board score
    for(int i=0; i<mark.size(); i++){
        pair<int, int> temp_hex = mark[i];
        cordinate2 temp = hex2cart[temp_hex];

        if(board_state1[temp.x][temp.y][temp.z] != -1){
            update_board_score(temp.x, temp.y, temp.z);
        }
    }
    return mark;
}

void remove_marker(int hex1, int pos1, int hex2, int pos2){
    vector<pair<int, int> > mark = places(hex1, pos1, hex2, pos2);

    for(int i=0; i<mark.size(); i++)
    {
        if( find(marker_self.begin(), marker_self.end(), mark[i]) != marker_self.end() ){
            marker_self.erase(remove(marker_self.begin(), marker_self.end(), mark[i]), marker_self.end());
        }
        else if( find(marker_opponent.begin(), marker_opponent.end(), mark[i]) != marker_opponent.end() ){
            marker_opponent.erase(remove(marker_opponent.begin(), marker_opponent.end(), mark[i]), marker_opponent.end());
        }
    }

    //removing the marker from the board_state
    for(int i=0; i<mark.size(); i++){
        pair<int, int> temp_hex = mark[i];
        cordinate2 temp = hex2cart[temp_hex];

        board_state1[temp.x][temp.y][temp.z] = -1;
        // vector<marker> board_x = board_state[temp.x][0];
        // for(int j=0; j<board_x.size(); j++){
        //     if(board_x[j].x == temp.y && board_x[j].y == temp.z){
        //         board_x.erase(board_x.begin() + j);
        //         j--;
        //         board_state[temp.x][0] = board_x;
        //         break;
        //     }
        // }
        // vector<marker> board_y = board_state[temp.y][1];
        // for(int j=0; j<board_y.size(); j++){
        //     if(board_y[j].x == temp.z && board_y[j].y == temp.x){
        //         board_y.erase(board_y.begin() + j);
        //         j--;
        //         board_state[temp.y][1] = board_y;
        //         break;
        //     }
        // }
        // vector<marker> board_z = board_state[temp.z][2];
        // for(int j=0; j<board_z.size(); j++){
        //     if(board_z[j].x == temp.x && board_z[j].y == temp.y){
        //         board_z.erase(board_z.begin() + j);
        //         j--;
        //         board_state[temp.z][2] = board_z;
        //         break;
        //     }
        // }
    }
    //update board score
    for(int i=0; i<mark.size(); i++){
        pair<int, int> temp_hex = mark[i];
        cordinate2 temp = hex2cart[temp_hex];

        update_board_score(temp.x, temp.y, temp.z);
    }
}

string get_move(){
    if(move_num<5){
        //placing the ring strategy: random ring strategy for now
        srand (time(NULL));
        int x_cord = rand()%11;

        int step = rand()%(bound_x[x_cord][2] - bound_x[x_cord][0]);
        int y_cord = step + bound_x[x_cord][0];
        int z_cord = step + bound_x[x_cord][1];

        pair<int, int> temp_cord = cart2hex[x_cord][y_cord][z_cord];
        while(exist_ring(temp_cord.first, temp_cord.second) != -1){
            x_cord = rand()%11;
            step = rand()%(bound_x[x_cord][2] - bound_x[x_cord][0]);
            y_cord = step + bound_x[x_cord][0];
            z_cord = step + bound_x[x_cord][1];
            temp_cord = cart2hex[x_cord][y_cord][z_cord];
        }
        string temp_move = "P " + to_string(temp_cord.first) + " " + to_string(temp_cord.second);
        move_num++;
        return temp_move;
    }
    else{
        //min-max declaration
        int min_gchild;
        int max_child = INT_MIN;
        pair<pair<int, int>, pair<int, int> > final_result;
        for(int i=0; i<5; i++){
            if(ring_self[i][0] != -1 && ring_self[i][1] != -1){
                cordinate2 temp_ring = hex2cart[pair<int, int>(ring_self[i][0], ring_self[i][1])];
                vector<cordinate2> pos = give_positions(temp_ring.x, temp_ring.y, temp_ring.z);
                for(int j=0; j<pos.size(); j++){
                    cordinate2 temp_pos = pos[j];
                    pair<int, int> hex_pos = cart2hex[temp_pos.x][temp_pos.y][temp_pos.z];
                    ring_update_self(ring_self[i][0], ring_self[i][1], hex_pos.first, hex_pos.second);
        			//marker update on the old ring position
        			add_marker_self(ring_self[i][0], ring_self[i][1]);
        			//switch the color of the markers in between
                    vector<pair<int, int> > v_child = switch_marker_return(ring_self[i][0], ring_self[i][1], hex_pos.first, hex_pos.second);
                    v_child.push_back(pair<int, int>(ring_self[i][0], ring_self[i][1]));
                    for(int k=0; k<v_child.size(); k++){
                        string temp_string = marker_5(v_child[k], i, hex_pos);
                        if(temp_string == "-1"){
                            v_child.erase(v_child.begin() + k );
                            k--;

                            //undo the move
                            ring_update_self(hex_pos.first, hex_pos.second, ring_self[i][0], ring_self[i][1]);
                            remove_single_marker(ring_self[i][0], ring_self[i][1]);
                            switch_marker(ring_self[i][0], ring_self[i][1], hex_pos.first, hex_pos.second);

                            continue;
                        }
                        else if(temp_string != ""){
                            //undo the move
                            ring_update_self(hex_pos.first, hex_pos.second, ring_self[i][0], ring_self[i][1]);
                            remove_single_marker(ring_self[i][0], ring_self[i][1]);
                            switch_marker(ring_self[i][0], ring_self[i][1], hex_pos.first, hex_pos.second);

                            return temp_string;
                        }
                    }

                    //no combination of 5 markers
                    //go one more layer into the children

                    //min initialize
                    min_gchild = INT_MAX;

                    for(int i_child=0; i_child<5; i_child++){
                        if(ring_self[i_child][0] != -1 && ring_self[i_child][1] != -1){
                            cordinate2 temp_ring_child = hex2cart[pair<int, int>(ring_self[i_child][0], ring_self[i_child][1])];

                            vector<cordinate2> pos_child = give_positions(temp_ring_child.x, temp_ring_child.y, temp_ring_child.z);
                            for(int j_child= 0; j_child< pos_child.size(); j_child++){
                                cordinate2 temp_pos_child = pos_child[j_child];
                                pair<int, int> hex_pos_child = cart2hex[temp_pos_child.x][temp_pos_child.y][temp_pos_child.z];
                                ring_update_self(hex_pos.first, hex_pos.second, hex_pos_child.first, hex_pos_child.second);
                                //marker update on the old ring position
                                add_marker_self(hex_pos.first, hex_pos.second);
                                vector<pair<int, int> > v_child_child = switch_marker_return(hex_pos.first, hex_pos.second, hex_pos_child.first, hex_pos_child.second);
                                v_child_child.push_back(pair<int, int>(hex_pos.first, hex_pos.second));
                                for(int k= 0; k< v_child_child.size(); k++){
                                    string temp_string = marker_5(v_child[k], i, hex_pos);
                                    if(temp_string == "-1"){
                                        v_child.erase(v_child.begin() + k );
                                        k--;

                                        //undo the move
                                        ring_update_self(hex_pos_child.first, hex_pos_child.second, hex_pos.first, hex_pos.second);
                                        remove_single_marker(hex_pos.first, hex_pos.second);
                                        switch_marker(hex_pos.first, hex_pos.second, hex_pos_child.first, hex_pos_child.second);

                                        //undo the parent
                                        ring_update_self(hex_pos.first, hex_pos.second, ring_self[i][0], ring_self[i][1]);
                                        remove_single_marker(ring_self[i][0], ring_self[i][1]);
                                        switch_marker(ring_self[i][0], ring_self[i][1], hex_pos.first, hex_pos.second);
                                        continue;
                                    }
                                    else if(temp_string != ""){
                                        //undo the move
                                        ring_update_self(hex_pos_child.first, hex_pos_child.second, hex_pos.first, hex_pos.second);
                                        remove_single_marker(hex_pos.first, hex_pos.second);
                                        switch_marker(hex_pos.first, hex_pos.second, hex_pos_child.first, hex_pos_child.second);

                                        //undo the parent
                                        ring_update_self(hex_pos.first, hex_pos.second, ring_self[i][0], ring_self[i][1]);
                                        remove_single_marker(ring_self[i][0], ring_self[i][1]);
                                        switch_marker(ring_self[i][0], ring_self[i][1], hex_pos.first, hex_pos.second);

                                        return temp_string;
                                    }
                                }

                                //min score of all grandchildren
                                if(total_score() < min_gchild){
                                    min_gchild = total_score();
                                }

                                //undo the children layer move
                                //undo the move
                                ring_update_self(hex_pos_child.first, hex_pos_child.second, hex_pos.first, hex_pos.second);
                                remove_single_marker(hex_pos.first, hex_pos.second);
                                switch_marker(hex_pos.first, hex_pos.second, hex_pos_child.first, hex_pos_child.second);
                            }
                        }
                    }

                    //max score of all children
                    if(total_score() > max_child){
                        max_child = total_score();
                        pair<int, int> final_start;
                        final_start = {ring_self[i][0], ring_self[i][1]};
                        final_result = {final_start, hex_pos};
                    }

                    //undo the move
                    ring_update_self(hex_pos.first, hex_pos.second, ring_self[i][0], ring_self[i][1]);
                    remove_single_marker(ring_self[i][0], ring_self[i][1]);
                    switch_marker(ring_self[i][0], ring_self[i][1], hex_pos.first, hex_pos.second);
                }


            }
        }
        //make string
        string ans = "S " + to_string((final_result.first).first) + " " + to_string((final_result.first).second);
        ans = ans + " M " + to_string((final_result.second).first) + " " + to_string((final_result.second).second);
        move_num++;

        return ans;
    }
    //added just random code
    // string temp = "none";
    // return temp;
}

void undo_update_opponent(string move){
    vector<string> segment;
	split(move, " ", segment);

	if (segment[0] == "P"){
		//Place your ring
		ring_remove_opponent(stoi(segment[1]), stoi(segment[2]));
	}
	else if (segment[0] == "S"){
		if(segment.size() == 6){
			ring_update_opponent(stoi(segment[4]), stoi(segment[5]), stoi(segment[1]), stoi(segment[2]));
			//marker update on the old ring position
			remove_single_marker(stoi(segment[1]), stoi(segment[2]));

			//switch the color of the markers in between
            switch_marker(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));
		}
		else if(segment.size() == 15){
            ring_add_opponent(stoi(segment[13]), stoi(segment[14]));

            //remove the markers from RS to RE
            add_multiple_marker_opponent(stoi(segment[7]), stoi(segment[8]), stoi(segment[10]), stoi(segment[11]));

            //switch the color of the markers in between
            switch_marker(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));

            //marker update on the old ring position
			remove_single_marker(stoi(segment[1]), stoi(segment[2]));

            ring_update_opponent(stoi(segment[4]), stoi(segment[5]), stoi(segment[1]), stoi(segment[2]));
		}
	}
	else if(segment[0] == "RS"){
        ring_add_opponent(stoi(segment[7]), stoi(segment[8]));

        //remove the markers from RS to RE
        add_multiple_marker_opponent(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));
	}
    else{

    }
}

void undo_update_self(string move){
    vector<string> segment;
	split(move, " ", segment);

	if (segment[0] == "P"){
		//Place your ring
		ring_remove_self(stoi(segment[1]), stoi(segment[2]));
	}
	else if (segment[0] == "S"){
		if(segment.size() == 6){
			ring_update_self(stoi(segment[4]), stoi(segment[5]), stoi(segment[1]), stoi(segment[2]));
			//marker update on the old ring position
			remove_single_marker(stoi(segment[1]), stoi(segment[2]));

			//switch the color of the markers in between
            switch_marker(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));
		}
		else if(segment.size() == 15){
            ring_add_self(stoi(segment[13]), stoi(segment[14]));

            //remove the markers from RS to RE
            add_multiple_marker_self(stoi(segment[7]), stoi(segment[8]), stoi(segment[10]), stoi(segment[11]));

            //switch the color of the markers in between
            switch_marker(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));

            //marker update on the old ring position
			remove_single_marker(stoi(segment[1]), stoi(segment[2]));

            ring_update_self(stoi(segment[4]), stoi(segment[5]), stoi(segment[1]), stoi(segment[2]));
		}
	}
    else if(segment[0] == "RS"){
        ring_add_self(stoi(segment[7]), stoi(segment[8]));

        //remove the markers from RS to RE
        add_multiple_marker_self(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));
    }
	else {

	}
}

void remove_single_marker(int hex, int pos){

    pair<int, int> temp_marker {hex, pos};
    //removing from the original data structure of the board

    if( find(marker_self.begin(), marker_self.end(), temp_marker) != marker_self.end() ){
        marker_self.erase(remove(marker_self.begin(), marker_self.end(), temp_marker), marker_self.end());
    }
    else if( find(marker_opponent.begin(), marker_opponent.end(), temp_marker) != marker_opponent.end() ){
        marker_opponent.erase(remove(marker_opponent.begin(), marker_opponent.end(), temp_marker), marker_opponent.end());
    }

    //removing from the new data-structure of the board
    pair<int, int> temp_hex = temp_marker;
    cordinate2 temp = hex2cart[temp_hex];

    board_state1[temp.x][temp.y][temp.z] = -1;
    // vector<marker> board_x = board_state[temp.x][0];
    // for(int j=0; j<board_x.size(); j++){
    //     if(board_x[j].x == temp.y && board_x[j].y == temp.z){
    //         board_x.erase(board_x.begin() + j);
    //         board_state[temp.x][0] = board_x;
    //         break;
    //     }
    // }
    // vector<marker> board_y = board_state[temp.y][1];
    // for(int j=0; j<board_y.size(); j++){
    //     if(board_y[j].x == temp.z && board_y[j].y == temp.x){
    //         board_y.erase(board_y.begin() + j);
    //         board_state[temp.y][1] = board_y;
    //         break;
    //     }
    // }
    // vector<marker> board_z = board_state[temp.z][2];
    // for(int j=0; j<board_z.size(); j++){
    //     if(board_z[j].x == temp.x && board_z[j].y == temp.y){
    //         board_z.erase(board_z.begin() + j);
    //         board_state[temp.z][2] = board_z;
    //         break;
    //     }
    // }

    update_board_score(temp.x, temp.y, temp.z);
}

void ring_add_self(int hex, int pos){
    for(int i=0; i<5; i++){
        if(ring_self[i][0] == -1 && ring_self[i][1] == -1){
            ring_self[i][0] = hex;
            ring_self[i][1] = pos;
            break;
        }
    }
}

void ring_add_opponent(int hex, int pos){
    for(int i=0; i<5; i++){
        if(ring_opponent[i][0] == -1 && ring_opponent[i][1] == -1){
            ring_opponent[i][0] = hex;
            ring_opponent[i][1] = pos;
            break;
        }
    }
}

void add_multiple_marker_self(int hex1, int pos1, int hex2, int pos2){
    //write for both the type of datastrutures
    vector<pair<int, int> > mark = places(hex1, pos1, hex2, pos2);

    for(int i=0; i<mark.size(); i++)
    {
        if( find(marker_self.begin(), marker_self.end(), mark[i]) != marker_self.end() ){
            marker_self.push_back(mark[i]);
        }
    }

    //adding the marker in board_state1
    for(int i=0; i<mark.size(); i++){
        pair<int, int> temp_hex = mark[i];
        cordinate2 temp = hex2cart[temp_hex];

        board_state1[temp.x][temp.y][temp.z] = 1;
    }

    for(int i=0; i<mark.size(); i++){
        pair<int, int> temp_hex = mark[i];
        cordinate2 temp = hex2cart[temp_hex];

        update_board_score(temp.x, temp.y, temp.z);
    }
}

void add_multiple_marker_opponent(int hex1, int pos1, int hex2, int pos2){
    //write for both the type of datastrutures
    vector<pair<int, int> > mark = places(hex1, pos1, hex2, pos2);

    for(int i=0; i<mark.size(); i++)
    {
        if( find(marker_opponent.begin(), marker_opponent.end(), mark[i]) != marker_opponent.end() ){
            marker_opponent.push_back(mark[i]);
        }
    }

    //adding the marker in board_state1
    for(int i=0; i<mark.size(); i++){
        pair<int, int> temp_hex = mark[i];
        cordinate2 temp = hex2cart[temp_hex];

        board_state1[temp.x][temp.y][temp.z] = 0;
    }

    for(int i=0; i<mark.size(); i++){
        pair<int, int> temp_hex = mark[i];
        cordinate2 temp = hex2cart[temp_hex];

        update_board_score(temp.x, temp.y, temp.z);
    }
}

int exist_ring(int hex, int pos){
    //return -1: does not exist, 0:opponent, 1:my ring
    for(int i=0; i<5; i++)
    {
        if(ring_self[i][0] == hex && ring_self[i][1] == pos){
            return 1;
        }
        if(ring_opponent[i][0] == hex && ring_opponent[i][1] == pos){
            return 0;
        }
    }
    int a = -1;
    return a;
}

string marker_5(pair<int, int> v, int i, pair<int, int> hex_pos){
    cordinate2 temp_child = hex2cart[v];
    if(board_state1[temp_child.x][temp_child.y][temp_child.z] != -1){
        pair<vector<pair<cordinate2, cordinate2>>, vector<pair<cordinate2, cordinate2> > > temp_check = check_5(temp_child.x, temp_child.y, temp_child.z);
        //if there exist a 5 for the opponent, remove it from the list
        //if there exist a 5 for me, then execute_move
        vector<pair<cordinate2, cordinate2> > temp_check_opponent = temp_check.second;
        vector<pair<cordinate2, cordinate2> > temp_check_self = temp_check.first;
        if(temp_check_opponent.size() > 0){
            // v_child.erase(v_child.begin() + k );
            return to_string(-1);
            // k--;
            // continue;
        }
        else if(temp_check_self.size() > 0){
            string temp_move = "S " + to_string(ring_self[i][0]) + " " + to_string(ring_self[i][1]) + " M " + to_string(hex_pos.first) + " " + to_string(hex_pos.second);
            cordinate2 cart_marker_start = temp_check_self[0].first;
            cordinate2 cart_marker_end = temp_check_self[0].second;
            pair<pair<int, int>, pair<int, int> > rem_marker_final = select_5(pair<cordinate2, cordinate2> (cart_marker_start, cart_marker_end));
            pair<int, int> hex_marker_start = rem_marker_final.first;
            pair<int, int> hex_marker_end = rem_marker_final.second;
            temp_move = temp_move + " RS " + to_string(hex_marker_start.first) + " " + to_string(hex_marker_start.second);
            temp_move = temp_move + " RE " + to_string(hex_marker_end.first) + " " + to_string(hex_marker_end.second);

            //choosing the ring to remove_marker
            int select_ring;
            srand (time(NULL));
            select_ring = rand()%5;
            while (ring_self[select_ring][0] == -1 || ring_self[select_ring][1] == -1) {
                select_ring = rand()%5;
            }
            temp_move = temp_move + " X " + to_string(ring_self[select_ring][0]) + " " + to_string(ring_self[select_ring][1]);

            return temp_move;
        }
    }
    string a = "";
    return a;
}
