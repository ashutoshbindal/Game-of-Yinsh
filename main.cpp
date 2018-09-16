#include <iostream>

#include "map.h"
#include "player.h"
#include "possible_moves.h"

using namespace std;

int main(int argc, char** argv) {

    int player_id, board_size, time_limit;
    string move;

    //initialize the conversion data structure in map.h
    initialize();
    place_bounds();
    initialize_score();
    initialize_board_state1();

    // Get input from server about game specifications
    cin >> player_id >> board_size >> time_limit;

    if(player_id == 2) {
        // Get other player's move
        cin>>move;
        update_opponent(move);

        while(true) {
        	move = get_move();
        	update_self(move);
            cout<<move<<endl;
            cin>>move;
            update_opponent(move);
        }
    }
    else if(player_id == 1) {
        while(true) {
        	move = get_move();
        	update_self(move);
            cout<<move<<endl;
            cin>>move;
            update_opponent(move);
        }
    }

    //testing the conversion data structure
    // pair<int, int> var_temp = {0, 0};
    // cordinate2 temp = hex2cart[var_temp];
    // cout<<temp.x<<" "<<temp.y<<" "<<temp.z<<endl;
    return 0;
}
