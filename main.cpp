#include <iostream>
#include <string>

#include "map.h"
#include "player.h"
#include "possible_moves.h"

using namespace std;

int main(int argc, char** argv) {

    int player_id, board_size, time_limit;
    string move_string;
    string random;

    //initialize the conversion data structure in map.h
    initialize();
    place_bounds();
    initialize_score();
    initialize_board_state1();
    initialize_player();

    // Get input from server about game specifications
    cin >> player_id >> board_size >> time_limit;
    getline(cin, random);
    // cout<<"stats:::"<<player_id<<" "<<board_size<<" "<<time_limit<<endl;
    if(player_id == 2) {
        global_move_flag = false;
        // Get other player's move
        getline(cin, move_string);
        // cout<<"main::::"<<move_string<<"#"<<endl;
        update_opponent(move_string);

        while(true) {
        	if(!global_move_flag)  move_string = get_move();
            else    move_string = check_move;
            // cout<<move_string<<endl;
        	update_self(move_string);
            // cout<<"##########################"<<endl;
            cout<<move_string<<endl;
            getline(cin, move_string);
            global_move_flag = false;
            update_opponent(move_string);
        }
    }
    else if(player_id == 1) {
        global_move_flag = false;
        while(true) {
            if(!global_move_flag)  move_string = get_move();
            else    move_string = check_move;
        	// cout<<move_string<<endl
        	update_self(move_string);
            cout<<move_string<<endl;
            getline(cin, move_string);
            global_move_flag = false;
            update_opponent(move_string);
        }
    }

    //testing the conversion data structure
    // pair<int, int> var_temp = {0, 0};
    // cordinate2 temp = hex2cart[var_temp];
    // cout<<temp.x<<" "<<temp.y<<" "<<temp.z<<endl;
    return 0;
}
