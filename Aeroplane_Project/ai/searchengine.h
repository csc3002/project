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
 * Method: play
 * Usage: searchengine.play(chessboard[16], side)
 * ---------------------------
 * This method simulates a player. It receives a chessboard
 * and returns the new chessboard.
 */

    void play(CHESS chessboard[],int side);

/*
 * Method: searchAGoodMove
 * Usage: searchAGoodMove(count, side, rollcount)
 * ---------------------------------------
 * This method is used to find the best move. When it is executed,
 * it will change the bestMoves pointer pointing to the best move
 * in the moveList.
 */
    void searchAGoodMove(int count, int side);


//  This two method set evaluator and move generator to the search engine.
    virtual void setEvaluator(evaluator * eval){pEval = eval;}
    virtual void setMoveGenerator(moveGenerator * MG){pMG = MG;}

    int rollPoint;

protected:

/*
 * Method: makeMove
 * Usage: makeMove(&move, chessboard, rollcount, side)
 * ---------------------------------------
 * This method receives a pointer to a chess move and a pointer to a chessboard.
 * The method will modify the chessboard according to the move.
 */

    void makeMove(CHESSMOVE * move, CHESS * chessboard, int side);


/*
 * Method: isGameOver
 * Usage: win = isGameOver(chessboard[16])
 * ---------------------------------------
 * This method is used to judge whether game is over.
 * It can be use when searching a good move. Probably
 * can be used in other situations.
 */
    bool isGameOver(const CHESS chessboard[]);


/*
 * Method: genOuterMove
 * Usage: genOuterMove()
 * ---------------------
 * This method generates the move from outer loop.
 */
    void genOuterMove(CHESS *chess, CHESS * chessboard, int side, int rollPoint, int off, int turn, int flyBegin, int flyEnd);

/*
 * Method: genInnerMove
 * Usage: genInnerMove()
 * ---------------------
 * This method generates the move from inner loop, including the turning point.
 */
    void genInnerMove(CHESS *chess, CHESS * chessboard, int rollPoint, int turn);

//  This array is the current chessboard
    CHESS cur_Chessboard [16];

//  This variable stores the current best move.
    CHESSMOVE * bestMove;

//  This is the pointer to the evaluator.
    evaluator * pEval;

// This is the pointer to the move generator.
    moveGenerator * pMG;

};

#endif // SEARCHENGINE_H
