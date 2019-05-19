/*
 * File: movegenerator.h
 * ---------------
 * This file is the move generator for the AI. It has the following functions:
 * 1. Initialize the game mode, such as deciding the taking off condition.
 * 2. Can create and store possible moves according to chessboard, roll point and side.
 * The moves it store can be accessed by the search engine and evaluator in order to
 * find the current best move.
 */

#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "define.h"

/*
 * Class: moveGenerator
 * ---------------------
 * This class is the move generator for an AI. It provides multiple methods
 * to generate all possible moves for certain roll points. It can also
 * store the possible move information.
 */

class moveGenerator
{

/*
 * Public field starts from here.
 */

public:

/*
 * Method: constructor and destructor
 * -------------------------------------
 * Constructor and destructor of the class instance.
 */

    moveGenerator(int offmode, int advance);
    virtual ~moveGenerator();

/*
 * Method: roll
 * Usage: int rollPoint = roll();
 * -------------------------------
 * This method simulates the dice rolling. It returns an integer between 1 to 6 randomly
 * each time being called.
 */

    int roll();


/*
 * Method: createPossibleMove
 * Usage: int moveCount = createPossibleMove(chessboard[16], rollPoint, side, hadCard)
 * ------------------------------------------------------------------------------------
 * This function can generate all possible moves of a player and return the number of moves.
 * It has 4 parameters. chessboard[] is an array which contains the current chessboard.
 * rollPoint is the roll point of current player. side is the color of the player. hadCard
 * is the information about the card this player currently hold.
 */

    virtual int createPossibleMove(const CHESS chessboard[], int rollPoint, int side, int hadCard);

//  This is the data structure which stores all possible moves.

    CHESSMOVE moveList[64];

//  This variable indicates the condition of taking off.
//  When dice roll is larger or equal to offMode, a plane
//  can take off.

    int offMode = 6;

//  This variable controls whether the advanced mode is on or off.
//  Default setting is off (0).

    int advanceMode = 0;

/*
 * Protected field starts from here.
 */

protected:

/*
 * Method: addMove
 * Usage: addMove(rollPoint, chessID, aboutCard)
 * ----------------------------------------------
 * Add a valid chess move to the move list.
 */

    void addMove(int rollPoint, int chessID, int aboutCard);

//  This variable stores the number of move generated at this stage.
    int moveCount;

};

#endif // MOVEGENERATOR_H
