#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

// Added private variables (Joo);
private:
    Board currentboard;
    Side ourSide;
    Side theirSide;
//(J)

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    Move *minimax(Move *opponentsMove, int msLeft, int depth);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
