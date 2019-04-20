/*
 * File: movegenerator.cpp
 * ------------------------
 * This file stores the implementation of move generator.
 */
#include<stdio.h>
#include<stdlib.h>
#include "define.h"
#include "movegenerator.h"

/*
 * Implementation note: constructor
 * ---------------------------------
 * The generator needs to set seeds when it is constructed.
 * It also sets the off mode.
 */

moveGenerator::moveGenerator(int offmode)
{
    offMode = offmode;
    srand(static_cast<unsigned>(time(nullptr)));
}

/*
 * Implementation note: destructor
 * ---------------------------------
 * The destructor of the generator.
 */
moveGenerator::~moveGenerator()
{

}

/*
 * Implementation note: roll
 * --------------------------
 * This method will set seed base on the system time so that
 * every game will generate different sequence of dice rolls.
 */

int moveGenerator::roll()
{
    int randNum;
    randNum = rand() % 6 + 1;
    return randNum;

}


/*
 * Implementation note: createPossibleMove
 * ----------------------------------------
 * Notice that this function will NOT change the current chessboard.
 */

int moveGenerator::createPossibleMove(const CHESS chessboard[], int rollPoint, int side){
    // selecting chesses according to player's side
    CHESS possible[5];
    possible[0].chessID = NOCHESS;
    possible[0].color = side;
    switch(side){
    case RED:{
        for(int i = 1; i <= 4; i++)
            possible[i] = chessboard[i-1];
        int off = RED_OFF;
        int turn = RED_TURN;
        int flyBegin = RED_FLY_BEGIN;
        int flyEnd = RED_FLY_END;
        break;
    }

    case YELLOW:{
        for(int i = 1; i <= 4; i++)
            possible[i] = chessboard[i+3];
        int off = YELLOW_OFF;
        int turn = YELLOW_TURN;
        int flyBegin = YELLOW_FLY_BEGIN;
        int flyEnd = YELLOW_FLY_END;
        break;
        }
    case BLUE:{
        for(int i = 1; i <= 4; i++)
            possible[i] = chessboard[i+7];
        int off = BLUE_OFF;
        int turn = BLUE_TURN;
        int flyBegin = BLUE_FLY_BEGIN;
        int flyEnd = BLUE_FLY_END;
        break;
        }
    case GREEN:{
        for(int i = 1; i <= 4; i++)
            possible[i] = chessboard[i+11];
        int off = GREEN_OFF;
        int turn = GREEN_TURN;
        int flyBegin = GREEN_FLY_BEGIN;
        int flyEnd = GREEN_FLY_END;
        break;
        }
    default:
            return -1;
    }

    // offCounts: use to eliminate repeat taking off
    int offCount = 0;
    // iterate all chesses:
    for(int i = 0; i < 5; i++){
        CHESS & nowChess = possible[i];
        if(nowChess.chessID == NOCHESS){
            addMove(rollPoint, nowChess.chessID);
            continue;
        }
        if(nowChess.currentCoor.region == WIN)
            continue;
        else if(nowChess.currentCoor.region == APRON){
            if(rollPoint >= offMode && offCount == 0){
                addMove(rollPoint, nowChess.chessID);
                offCount++;
            }
            else
                continue;
        }
        else
            addMove(rollPoint, nowChess.chessID);
    }
    return moveCount;
}

/*
 * Implementation note: chessID
 * ------------------------------
 * The implementation of addMove.
 */


void moveGenerator::addMove(int rollPoint, int chessID){
    moveList[moveCount].rollPoint = rollPoint;
    moveList[moveCount].chessID = chessID;
    moveCount++;
}












