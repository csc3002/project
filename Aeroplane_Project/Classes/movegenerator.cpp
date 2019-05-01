/*
 * File: movegenerator.cpp
 * ------------------------
 * This file stores the implementation of move generator.
 */
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<ctime>
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
 * Also this method does not check how many times does the dice roll.
 */

int moveGenerator::createPossibleMove(const CHESS chessboard[], int rollPoint, int side){
    moveCount = 0;
    // selecting chesses according to player's side
    CHESS possible[5];
    possible[0].chessID = NOCHESS;
    possible[0].color = side;
    // select the chess bas on side
    switch(side){
    case RED:{
        for(int i = 1; i <= 4; i++)
            possible[i] = chessboard[i-1];
        break;
    }

    case YELLOW:{
        for(int i = 1; i <= 4; i++)
            possible[i] = chessboard[i+3];
        break;
        }
    case BLUE:{
        for(int i = 1; i <= 4; i++)
            possible[i] = chessboard[i+7];
        break;
        }
    case GREEN:{
        for(int i = 1; i <= 4; i++)
            possible[i] = chessboard[i+11];
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
        if(nowChess.chessID == NOCHESS){            // do not move is always avaliable
            addMove(rollPoint, nowChess.chessID);
            std::cout << "add no chess, chessId = "<< nowChess.chessID << ", roll point = "<< rollPoint << std::endl;
            continue;
        }
        if(nowChess.currentCoor.region == WIN)      // skip the chesses already win
            continue;
        else if(nowChess.currentCoor.region == APRON){
            if(rollPoint >= offMode && offCount == 0){      // special treatement for taking off:
                addMove(rollPoint, nowChess.chessID);       // taking off just counts once
                offCount++;
                std::cout << "add take off, chessId = "<< nowChess.chessID << ", roll point = "<< rollPoint << std::endl;
            }
            else
                continue;
        }
        else{       // else are the situations that move a chess on the chessboard
            addMove(rollPoint, nowChess.chessID);
            std::cout << "add move a chess,chessId = "<< nowChess.chessID << ", roll point = "<< rollPoint << std::endl;
        }
    }
    std::cout <<"how many moves: " << moveCount<< std::endl;
    return moveCount;
}

/*
 * Implementation note: addMove
 * ------------------------------
 * The implementation of addMove. It will modify moveList and increase moveCount
 * by one once it is called.
 */

void moveGenerator::addMove(int rollPoint, int chessID){
    moveList[moveCount].rollPoint = rollPoint;
    moveList[moveCount].chessID = chessID;
    moveCount++;
    std::cout << moveCount << ": ";
}


