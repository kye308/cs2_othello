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

    static const int CORNER = 10;
    static const int EDGE = 3;
    static const int NEAR_CORNER = -15;

//(J)

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    Move *minimax(Move *opponentsMove, int msLeft, int depth);
    void setBoard(Board b);
    bool isEdge(Move *m);
    bool isCorner(Move *m);
    bool nearCorner(Move *m);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
