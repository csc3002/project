/*
 * File: evaluator.h
 * -----------------
 * This is the head file of simple evaluator.The main method evaluate() just
 * evaluate the value of a move.
 */

#include "define.h"
#include "math.h"

#ifndef EVALUATOR_H
#define EVALUATOR_H


class evaluator
{
public:

// constructor and destructor
    evaluator();
    virtual ~evaluator();

/*
 * Method: evaluate
 * Usage: score = evaluate(chessboard[16], side)
 * ---------------------------------------------
 * This method can return the value of a chessboard situation base on the side of the player.
 */

    virtual int evaluate(const CHESS oldChessboard[],const CHESS newChessboard[], int side);
};

#endif // EVALUATOR_H
