#include <iostream>
#include <string>
#include <vector>

#include "player.h"

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
		}
		else if(segment.size() == 15){
			ring_update_self(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));
			//marker update on the old ring position
			add_marker_self(stoi(segment[1]), stoi(segment[2]));

			//switch the color of the markers in between
			//remove the markers from RS to RE

			ring_remove_self(stoi(segment[13]), stoi(segment[14]));
		}
	}
	else{

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
		}
		else if(segment.size() == 15){
			ring_update_opponent(stoi(segment[1]), stoi(segment[2]), stoi(segment[4]), stoi(segment[5]));
			//marker update on the old ring position
			add_marker_opponent(stoi(segment[1]), stoi(segment[2]));

			//switch the color of the markers in between
			//remove the markers from RS to RE

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
}

void player::add_marker_opponent(int hex, int pos){
	marker_opponent.push_back(pair<int, int>(hex, pos));
}

string player::get_move(){

    //added just random code
    string temp = "none";
    return temp;
}

// void player::update_board(string move, int player){
// 	//player = 0 => self
//
// }
