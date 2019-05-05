/*
 * File: searchengin.h
 * ----------------------
 * This file is the core logic for traditional aeroplane AI. It can simulates a
 * player's behavior.
 * The main function is play(), which accepts a chessboard and the side of this
 * player. Once it is called, it will roll dice and choose move like human players,
 * and it will change the chessboard in place.
 */

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
 * and change the original chessboard in place.
 */

    virtual void play(CHESS chessboard[],int side);

/*
 * Method: searchAGoodMove
 * Usage: searchAGoodMove(count, side, rollcount)
 * ---------------------------------------
 * This method is used to find the best move. When it is executed,
 * it will change the bestMoves pointer pointing to the best move
 * in the moveList.
 */
    virtual void searchAGoodMove(int count, int side);


/*
 * Method: isGameOver
 * Usage: win = isGameOver(chessboard[16])
 * ---------------------------------------
 * This method is used to judge whether game is over.
 * It can be use when searching a good move. Probably
 * can be used in other situations.
 */
    bool isGameOver(const CHESS chessboard[]);

//  This two method set evaluator and move generator to the search engine.
    virtual void setEvaluator(evaluator * eval){pEval = eval;}
    virtual void setMoveGenerator(moveGenerator * MG){pMG = MG;}

//  This variable preserves the roll point
    int rollPoint;
// Testing variable:jinx count
    int jinxCount = 0;

protected:

/*
 * Method: makeMove
 * Usage: makeMove(&move, chessboard, rollcount, side)
 * ---------------------------------------
 * This method receives a pointer to a chess move and a pointer to a chessboard.
 * The method will modify the chessboard according to the move.
 */

    virtual void makeMove(CHESSMOVE * move, CHESS * chessboard, int side);

/*
 * Method: genOuterMove
 * Usage: genOuterMove()
 * ---------------------
 * This method generates the move from outer loop.
 */

    virtual void genOuterMove(CHESS *chess, CHESS * chessboard, int side, int rollPoint, int off, int turn, int flyBegin, int flyEnd);

/*
 * Method: genInnerMove
 * Usage: genInnerMove()
 * ---------------------
 * This method generates the move from inner loop, including the turning point.
 */

    virtual void genInnerMove(CHESS *chess, int rollPoint, int turn);

//  This array is the current chessboard
    CHESS cur_Chessboard [16];

//  This variable stores the current best move.
    CHESSMOVE * bestMove = nullptr;

//  This is the pointer to the evaluator.
    evaluator * pEval;

// This is the pointer to the move generator.
    moveGenerator * pMG;

};

#endif // SEARCHENGINE_H
