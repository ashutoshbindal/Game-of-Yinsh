#include <iostream>
#include <string>
#include <vector>

#include "player.h"
#include "map.h"
#include "possible_moves.h"

using namespace std;

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

player::player(){
	number_ring_self = 0;
	number_ring_opponent = 0;

	//Initialize for all the ring position to -1
	for(int i=0; i<5; i++)
	{
		ring_self[i][0] = -1;
		ring_self[i][1] = -1;
		ring_opponent[i][0] = -1;
		ring_opponent[i][1] = -1;
	}
}

int player::eval_func(){
    int s;
	return s;
}

void player::update_self(string move){
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
	else {

	}
}

void player::update_opponent(string move){
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
	else{

	}
}

void player::place_ring_self(int hex, int pos){
	number_ring_self++;
	ring_self[number_ring_self-1][0] = hex;
	ring_self[number_ring_self-1][1] = pos;
}

void player::place_ring_opponent(int hex, int pos){
	number_ring_opponent++;
	ring_opponent[number_ring_opponent-1][0] = hex;
	ring_opponent[number_ring_opponent-1][1] = pos;
}

void player::ring_update_self(int old_hex, int old_pos, int new_hex, int new_pos){
	for(int i=0; i<5; i++){
		if(ring_self[i][0] == old_hex && ring_self[i][1] == old_pos){
			ring_self[i][0] = new_hex;
			ring_self[i][1] = new_pos;
			break;
		}
	}
}

void player::ring_update_opponent(int old_hex, int old_pos, int new_hex, int new_pos){
	for(int i=0; i<5; i++){
		if(ring_opponent[i][0] == old_hex && ring_opponent[i][1] == old_pos){
			ring_opponent[i][0] = new_hex;
			ring_opponent[i][1] = new_pos;
			break;
		}
	}
}

void player::ring_remove_self(int hex, int pos){
	for(int i=0; i<5; i++){
		if(ring_self[i][0] == hex && ring_self[i][1] == pos){
			ring_self[i][0] = -1;
			ring_self[i][1] = -1;
			number_ring_self--;
			break;
 		}
	}
}

void player::ring_remove_opponent(int hex, int pos){
	for(int i=0; i<5; i++){
		if(ring_opponent[i][0] == hex && ring_opponent[i][1] == pos){
			ring_opponent[i][0] = -1;
			ring_opponent[i][1] = -1;
			number_ring_opponent--;
			break;
		}
	}
}

void player::add_marker_self(int hex, int pos){
	marker_self.push_back(pair<int, int>(hex, pos));

    //adding the marker to board_state
    cordinate2 temp_marker = hex2cart[pair<int, int>(hex, pos)];
    marker m1 (temp_marker.y, temp_marker.z, true);
    marker m2 (temp_marker.z, temp_marker.x, true);
    marker m3 (temp_marker.x, temp_marker.y, true);
    board_state[temp_marker.x][0].push_back(m1);
    board_state[temp_marker.y][1].push_back(m2);
    board_state[temp_marker.z][2].push_back(m3);
}

void player::add_marker_opponent(int hex, int pos){
	marker_opponent.push_back(pair<int, int>(hex, pos));

    //adding the marker to board_state
    cordinate2 temp_marker = hex2cart[pair<int, int>(hex, pos)];
    marker m1 (temp_marker.y, temp_marker.z, false);
    marker m2 (temp_marker.z, temp_marker.x, false);
    marker m3 (temp_marker.x, temp_marker.y, false);
    board_state[temp_marker.x][0].push_back(m1);
    board_state[temp_marker.y][1].push_back(m2);
    board_state[temp_marker.z][2].push_back(m3);
}

void player::switch_marker(int hex1, int pos1, int hex2, int pos2){
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

    //switching the markers on the board_sta
    for(int i=0; i<mark.size(); i++){
        pair<int, int> temp_hex = mark[i];
        cordinate2 temp = hex2cart[temp_hex];

        //checking along each axis for the marker and flipping
        vector<marker> board_x = board_state[temp.x][0];
        for(int j=0; j<board_x.size(); j++){
            if(board_x[j].x == temp.y && board_x[j].y == temp.z){
                board_x[j].token ^= true;
                board_state[temp.x][0] = board_x;
                break;
            }
        }
        vector<marker> board_y = board_state[temp.y][1];
        for(int j=0; j<board_y.size(); j++){
            if(board_y[j].x == temp.z && board_y[j].y == temp.x){
                board_y[j].token ^= true;
                board_state[temp.y][1] = board_y;
                break;
            }
        }
        vector<marker> board_z = board_state[temp.z][2];
        for(int j=0; j<board_z.size(); j++){
            if(board_z[j].x == temp.x && board_z[j].y == temp.y){
                board_z[j].token ^= true;
                board_state[temp.z][2] = board_z;
                break;
            }
        }
    }
}

void player::remove_marker(int hex1, int pos1, int hex2, int pos2){
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

        vector<marker> board_x = board_state[temp.x][0];
        for(int j=0; j<board_x.size(); j++){
            if(board_x[j].x == temp.y && board_x[j].y == temp.z){
                board_x.erase(board_x.begin() + j);
                j--;
                board_state[temp.x][0] = board_x;
                break;
            }
        }
        vector<marker> board_y = board_state[temp.y][1];
        for(int j=0; j<board_y.size(); j++){
            if(board_y[j].x == temp.z && board_y[j].y == temp.x){
                board_y.erase(board_y.begin() + j);
                j--;
                board_state[temp.y][1] = board_y;
                break;
            }
        }
        vector<marker> board_z = board_state[temp.z][2];
        for(int j=0; j<board_z.size(); j++){
            if(board_z[j].x == temp.x && board_z[j].y == temp.y){
                board_z.erase(board_z.begin() + j);
                j--;
                board_state[temp.z][2] = board_z;
                break;
            }
        }
    }
}

string player::get_move(){

    //added just random code
    string temp = "none";
    return temp;
}

void player::undo_update_opponent(string move){
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
			ring_update_opponent(stoi(segment[4]), stoi(segment[5]), stoi(segment[1]), stoi(segment[2]));
			//marker update on the old ring position
			remove_single_marker(stoi(segment[1]), stoi(segment[2]));

			//switch the color of the markers in between
            switch_marker(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));

			//remove the markers from RS to RE
            remove_marker(stoi(segment[7]), stoi(segment[8]), stoi(segment[10]), stoi(segment[11]));

			ring_add_opponent(stoi(segment[13]), stoi(segment[14]));
		}
	}
	else{

	}
}

void player::undo_update_self(string move){
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
			ring_update_self(stoi(segment[4]), stoi(segment[5]), stoi(segment[1]), stoi(segment[2]));
			//marker update on the old ring position
			remove_single_marker(stoi(segment[1]), stoi(segment[2]));

			//switch the color of the markers in between
            switch_marker(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));

			//remove the markers from RS to RE
            remove_marker(stoi(segment[7]), stoi(segment[8]), stoi(segment[10]), stoi(segment[11]));

			ring_add_self(stoi(segment[13]), stoi(segment[14]));
		}
	}
	else {

	}
}

void player::remove_single_marker(int hex, int pos){

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

    vector<marker> board_x = board_state[temp.x][0];
    for(int j=0; j<board_x.size(); j++){
        if(board_x[j].x == temp.y && board_x[j].y == temp.z){
            board_x.erase(board_x.begin() + j);
            board_state[temp.x][0] = board_x;
            break;
        }
    }
    vector<marker> board_y = board_state[temp.y][1];
    for(int j=0; j<board_y.size(); j++){
        if(board_y[j].x == temp.z && board_y[j].y == temp.x){
            board_y.erase(board_y.begin() + j);
            board_state[temp.y][1] = board_y;
            break;
        }
    }
    vector<marker> board_z = board_state[temp.z][2];
    for(int j=0; j<board_z.size(); j++){
        if(board_z[j].x == temp.x && board_z[j].y == temp.y){
            board_z.erase(board_z.begin() + j);
            board_state[temp.z][2] = board_z;
            break;
        }
    }
}

void player::ring_add_self(int hex, int pos){
    for(int i=0; i<5; i++){
        if(ring_self[i][0] == -1 && ring_self[i][1] == -1){
            ring_self[i][0] = hex;
            ring_self[i][1] = pos;
            break;
        }
    }
}

void player::ring_add_opponent(int hex, int pos){
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
}

void add_multiple_marker_opponent(int hex1, int pos1, int hex2, int pos2){
    //write for both the type of datastrutures
}
