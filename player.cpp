#include "player.h"
#include <cstdio>
#include <vector>

// edited file

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    // Created new initial board instance (Joo)
    this->currentboard = Board();
    // Keep track of which side our AI is on (Joo)
    this->ourSide = side;
    // Keep track of side opponent's AI is on (Joo)
    if (ourSide == BLACK) {
        this->theirSide = WHITE;
    }
    else {
        this->theirSide = BLACK;
    }
    //(J)

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

     // Our lovely initialization
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
    
    // Do opponent's move (Joo);
    if (opponentsMove != NULL) {
        this->currentboard.doMove(opponentsMove, this->theirSide);
    }
    //(J)

    // No heuristic function, just do first possible move (Joo);
    if (currentboard.isDone() == true) {
        return NULL;
    }

    // find all valid moves
    vector<Move*> validMoves;

    if (currentboard.hasMoves(this->ourSide) == true) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move* tempmove = new Move(i, j);
                if (currentboard.checkMove(tempmove, this->ourSide)) {
                    validMoves.push_back(tempmove);               
                }
            }
        }
        //choose move heuristic:
    
        // Choose corner piece if possible
        for (unsigned int move = 0; move < validMoves.size(); move++) {
            if (validMoves[move]->x == 0 || validMoves[move]->x == 7){
                if (validMoves[move]->y == 0 || validMoves[move]->y == 7) {
                    currentboard.doMove(validMoves[move], this->ourSide);
                    return validMoves[move];
                }
            }
        }

        // Choose edge piece if possible
        for (unsigned int move = 0; move < validMoves.size(); move++) {
            if (((validMoves[move]->x == 0 || validMoves[move]->x == 7) && (validMoves[move]->y != 1 && validMoves[move]->y != 6)) ||
                ((validMoves[move]->y == 0 || validMoves[move]->y == 7) && (validMoves[move]->x != 1 && validMoves[move]->y != 6))) {
                currentboard.doMove(validMoves[move], this->ourSide);
                return validMoves[move];
            }
        }


        // otherwise just return greedily best move possible without looking ahead, but skips
        // spaces diagonal to corners (Not sure if this actually works better or worse though)
        int maxCount = 0;
        unsigned int maxMove = 0;
        for (unsigned int move = 0; move < validMoves.size(); move++) {
            if (!((validMoves[move]->x == 1 && validMoves[move]->y == 1) || 
                (validMoves[move]->x == 1 && validMoves[move]->y == 6) ||
                (validMoves[move]->x == 6 && validMoves[move]->y == 1) ||
                (validMoves[move]->x == 6 && validMoves[move]->y == 6))) {

                Board* tempboard = currentboard.copy();
                tempboard->doMove(validMoves[move], this->ourSide);

                if (tempboard->count(ourSide) > maxCount) {
                    maxCount = tempboard->count(ourSide);
                    maxMove = move;
               }
            }
        }
        currentboard.doMove(validMoves[maxMove], ourSide);
        return validMoves[maxMove];
    }
    


    // otherwise pass
    currentboard.doMove(NULL, this->ourSide);
    //(J)

    return NULL;
}





