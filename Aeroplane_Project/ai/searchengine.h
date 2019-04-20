//TODO: file description

#include "define.h"
#include "movegenerator.h"
#include "evaluator.h"
#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H


class searchEngine
{
public:

//  constructor and destructor
    searchEngine();
    virtual ~searchEngine();

/*
 * Method: searchAGoodMove
 * Usage:
 */
    void searchAGoodMove(CHESS chessboard[]);


//  This two method set evaluator and move generator to the search engine.
    virtual void setEvaluator(evaluator * eval){pEval = eval;}
    virtual void setMoveGenerator(moveGenerator * MG){pMG = MG;}

protected:

    void makeMove(CHESSMOVE * move);

    void unmakeMove(CHESSMOVE * move, int eaten[]);

    int isGameOver(CHESS chessboard[]);


/*
 * Method: genOuterMove
 * Usage: genOuterMove()
 * ---------------------
 * This method generates the move from outer loop.
 */
    void genOuterMove(CHESS &chess, int rollPoint, int off, int turn, int flyBegin, int flyEnd);

/*
 * Method: genInnerMove
 * Usage: genInnerMove()
 * ---------------------
 * This method generates the move from inner loop, including the turning point.
 */
    void genInnerMove(CHESS &chess, int rollPoint, int turn);

//  This array is the current chessboard
    CHESS cur_Chessboard [16];

//  This variable stores the current best move.
    CHESSMOVE bestMove;

//  This is the pointer to the evaluator.
    evaluator * pEval;

// This is the pointer to the move generator.
    moveGenerator * pMG;

};

#endif // SEARCHENGINE_H
