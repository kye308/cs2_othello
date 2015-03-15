#include "player.h"
#include <cstdio>
#include <vector>
#include <time.h>

// edited file

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = true;

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
    
    if (testingMinimax)
             return minimax(opponentsMove, msLeft, 1);

    // Do opponent's move (Joo);
    if (opponentsMove != NULL) {
        this->currentboard.doMove(opponentsMove, this->theirSide);
    }
    //(J)

    // No heuristic function, just do first possible move (Joo);
    if (currentboard.isDone()) {
        return NULL;
    }

    // find all valid moves
    vector<Move*> validMoves;

    if (currentboard.hasMoves(this->ourSide)) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move* tempmove = new Move(i, j);
                if (currentboard.checkMove(tempmove, this->ourSide)) {
                    validMoves.push_back(tempmove);               
                }
            }
        }

        //choose move heuristic:
        int maxCount = -99999;
        unsigned int maxMove = 0;
        for (unsigned int move = 0; move < validMoves.size(); move++) {
            Board* tempboard = currentboard.copy();
            tempboard->doMove(validMoves[move], this->ourSide);
            int moveValue;
            
            // Corner case, moveValue increased by 10
            if (validMoves[move]->x == 0 || validMoves[move]->x == 7){
                if (validMoves[move]->y == 0 || validMoves[move]->y == 7) {
                    moveValue = tempboard->count(ourSide) - tempboard->count(theirSide) + 10;
                }
            }

            // Edge case, moveValue increased by 2
            else if (((validMoves[move]->x == 0 || validMoves[move]->x == 7) && (validMoves[move]->y != 1 && validMoves[move]->y != 6)) ||
                ((validMoves[move]->y == 0 || validMoves[move]->y == 7) && (validMoves[move]->x != 1 && validMoves[move]->y != 6))) {
                moveValue = tempboard->count(ourSide) - tempboard->count(theirSide) + 2;
            }

            // Diagonal to corner, moveValue decreased by 5
            else if (!((validMoves[move]->x == 1 && validMoves[move]->y == 1) || 
                (validMoves[move]->x == 1 && validMoves[move]->y == 6) ||
                (validMoves[move]->x == 6 && validMoves[move]->y == 1) ||
                (validMoves[move]->x == 6 && validMoves[move]->y == 6))) {
                moveValue = tempboard->count(ourSide) - tempboard->count(theirSide) - 5;
            }

            // Anywhere in 1st or 6th column/row, decreased by 1
            else if ((validMoves[move]->x == 1 || validMoves[move]->y == 1 || 
                      validMoves[move]->x == 6 || validMoves[move]->y == 6)){
                moveValue = tempboard->count(ourSide) - tempboard->count(theirSide) - 5;
            }    
            // otherwise unchanged
            else {
                moveValue = tempboard->count(ourSide) - tempboard->count(theirSide);
            }

            if (moveValue > maxCount) {
                maxCount = moveValue;
                maxMove = move;
            }
        }

        // Now, we have best adjusted move, and we do it.
        currentboard.doMove(validMoves[maxMove], ourSide);
        return validMoves[maxMove];
    }

    // otherwise pass
    currentboard.doMove(NULL, this->ourSide);
    //(J)

    return NULL;


}

void Player::setBoard(Board b)
{
    currentboard = b;
}

Move *Player::minimax(Move *opponentsMove, int msLeft, int depth)
{   
    // Set the clock
    clock_t start = time(0);

    int minimax_depth = 2;

    // SET DEPTH HERE
    if (depth == minimax_depth)
    {   
        // depth is even, so we try to minimize the score
        if (depth % 2 == 0)
        {
            vector<Move *> valid_comp_moves;
            if (currentboard.hasMoves(this->theirSide))
            {
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        Move* tempmove = new Move(i, j);
                        if (currentboard.checkMove(tempmove, this->theirSide)) {
                            valid_comp_moves.push_back(tempmove);               
                        }
                    }
                } 
            
            // The score we want to minimize
            int min_count = 64;
            unsigned int minMove = 0;
            for (unsigned int move = 0; move < valid_comp_moves.size(); move++)
            {
                Board *tempboard = currentboard.copy();
                tempboard->doMove(valid_comp_moves[move], this->theirSide);
                int moveValue = tempboard->count(theirSide) - tempboard->count(ourSide);

                if (moveValue < min_count)
                {
                    min_count = moveValue;
                    minMove = move;
                }

            }
            std::cerr << "Minimum move " << minMove << std::endl;
            return valid_comp_moves[minMove];

            }
            // No valid moves for computer
            return NULL;
        }
        // Otherwise we try to maximize our score
        else
        {
            vector<Move *> valid_user_moves;

            if (currentboard.hasMoves(ourSide))
            {
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        Move *tempmove = new Move(i, j);
                        if (currentboard.checkMove(tempmove, ourSide))
                        {
                            valid_user_moves.push_back(tempmove);
                        }
                    }
                }

                // We want to maximize our score
                int max_count = -64;
                unsigned int maxMove = 0;

                for (unsigned int move = 0; 
                    move < valid_user_moves.size(); move++)
                {
                    Board *tempboard = currentboard.copy();
                    tempboard->doMove(valid_user_moves[move], ourSide);
                    int moveValue = tempboard->count(ourSide) - tempboard->count(theirSide);

                    if (moveValue > max_count)
                    {
                        max_count = moveValue;
                        maxMove = move;
                    }
                }   
                return valid_user_moves[maxMove];
            }
            // We have no moves
            return NULL;
        }
    }

        


    if (opponentsMove != NULL)
    {
        this->currentboard.doMove(opponentsMove, this->theirSide);
    }

    // Checking if the board is done
    if (currentboard.isDone())
    {
        return NULL;
    }

    // Find all valid moves
    vector<Move *> validMoves;

    // Depth is even, we minimize the opponent's move
    if (depth % 2 == 0)
    {   
        if (currentboard.hasMoves(theirSide))
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Move *tempmove = new Move(i, j);
                    if (currentboard.checkMove(tempmove, theirSide))
                    {
                        validMoves.push_back(tempmove);
                    }
                }
            }

            // The score we want to minimize
            int min_count = 64;
            Move *best = NULL;
            for (unsigned int move = 0; move < validMoves.size(); move++)
            {
                int seconds_elapsed = difftime(time(0), start);
                Move *best_move = minimax(validMoves[move], msLeft - seconds_elapsed, depth + 1);

                Board *tempboard = currentboard.copy();
                tempboard->doMove(best_move, ourSide);
                int moveValue = tempboard->count(theirSide) - tempboard->count(ourSide);

                if (moveValue < min_count)
                {
                    min_count = moveValue;
                    best = validMoves[move];
                }
            }
            currentboard.doMove(best, this->theirSide);
            return best;
        }
    }


    // Else we maximize our move
    else
    {
        if (currentboard.hasMoves(this->ourSide))
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Move *tempmove = new Move(i, j);
                    if (currentboard.checkMove(tempmove, ourSide))
                    {
                        validMoves.push_back(tempmove);
                    }
                }
            }
            std::cerr << "Valid moves size " << validMoves.size() << std::endl;
            int largest_score = -64;
            Move *best = NULL;

            // It's not our opponent's turn. I don't have to calculate
            // score....this is a pretty bad idea!
            // Actually this might only be reached when depth is not 2...

            for (unsigned int move = 0; move < validMoves.size(); move++)
            {
                int seconds_elapsed = difftime(time(0), start);
                Move *best_move = minimax(validMoves[move], msLeft - seconds_elapsed, depth + 1);
                

                Board *tempboard = currentboard.copy();
                tempboard->doMove(best_move, theirSide);
                int max_val = tempboard->count(ourSide) - tempboard->count(theirSide);
                std::cerr << "Max val (ours - theirs)" << max_val << std::endl;

                if (max_val > largest_score)
                {
                    largest_score = max_val;
                    best = validMoves[move];
                }
            }
                
            
            currentboard.doMove(best, this->ourSide);
            return best;


        }
        // We have no moves :(
        return NULL;
    }
    // This shouldn't be reached??
    return NULL;
}





