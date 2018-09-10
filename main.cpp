#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    int player_id, board_size, time_limit;
    string move;
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
    return 0;
}
