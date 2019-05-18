/*
 * File: movegenerator.cpp
 * ------------------------
 * This file stores the implementation of move generator.
 */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "define.h"
#include "movegenerator.h"

/*
 * Implementation note: constructor
 * ---------------------------------
 * The generator needs to set seeds when it is constructed.
 * It also sets the off mode and advance mode. Off mode means
 * the condition of taking off a chess. For example, offmode=6
 * means chess can take of only if dice roll is larger or equal to 6.
 * The parameter advance sets whether the AI is a simple AI or an advanced
 * AI. When advance=0, the AI is simple; when advance = 1, the AI is advanced.
 */

moveGenerator::moveGenerator(int offmode, int advance)
{
    offMode = offmode;
    advanceMode = advance;
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

int moveGenerator::createPossibleMove(const CHESS chessboard[], int rollPoint, int side, int hadCard){
    moveCount = 0;
    // selecting chesses according to player's side
    CHESS my_chess[5];
    my_chess[0].chessID = NOCHESS;
    my_chess[0].color = side;
    // select the chess bas on side
    switch(side){
    case RED:{
        for(int i = 1; i <= 4; i++)
            my_chess[i] = chessboard[i-1];
        break;
    }

    case YELLOW:{
        for(int i = 1; i <= 4; i++)
            my_chess[i] = chessboard[i+3];
        break;
        }
    case BLUE:{
        for(int i = 1; i <= 4; i++)
            my_chess[i] = chessboard[i+7];
        break;
        }
    case GREEN:{
        for(int i = 1; i <= 4; i++)
            my_chess[i] = chessboard[i+11];
        break;
        }
    default:
            return -1;
    }

    // offCounts: use to eliminate repeat taking off
    int offCount = 0;
    // iterate all own chesses:
    for(int i = 0; i < 5; i++){
        CHESS & nowChess = my_chess[i];
        if(nowChess.chessID == NOCHESS){            // do not move is always avaliable
            addMove(rollPoint, nowChess.chessID, NOCARD);
            std::cout << "add no chess, chessId = "<< nowChess.chessID << ", roll point = "<< rollPoint << std::endl;
            continue;
        }
        if(nowChess.currentCoor.region == WIN)      // skip the chesses already win
            continue;
        else if(nowChess.currentCoor.region == APRON){
            if(rollPoint >= offMode && offCount == 0){      // special treatement for taking off:
                addMove(rollPoint, nowChess.chessID, NOCARD);       // taking off just counts once
                offCount++;
                std::cout << "add take off, chessId = "<< nowChess.chessID << ", roll point = "<< rollPoint << std::endl;
            }
            else
                continue;
        }
        else{       // else are the situations that move a chess on the chessboard
            if(nowChess.buff_state != INTERFERED){
                addMove(rollPoint, nowChess.chessID, NOCARD);
                std::cout << "add move a chess,chessId = "<< nowChess.chessID << ", buff_state = "<< nowChess.buff_state <<", roll point = "<< rollPoint << std::endl;
             }
        }
    }

    if (advanceMode){
        // generate draw card if possible
        if(rollPoint == 1 || rollPoint == 6) {
            addMove(rollPoint, NOCHESS, DRAW);
            std::cout << "draw a card" << std::endl;
        }

        // generate card use if possible
        if(hadCard > 0) {
            switch (hadCard) {
            case ATTACK:{
                for(int i = 1; i <= 4; i++) {
                    if(my_chess[i].currentCoor.region == OUTERLOOP && my_chess[i].buff_state != INTERFERED) {
                        addMove(rollPoint, my_chess[i].chessID, ATTACK);
                        std::cout << "attack " << my_chess[i].chessID << std::endl;

                    }
                }
                break;
            }
            case DEFENSE:{
                for(int i = 1; i <= 4; i++) {
                    if(my_chess[i].currentCoor.region == OUTERLOOP && my_chess[i].buff_state != INTERFERED) {
                        addMove(rollPoint, my_chess[i].chessID, DEFENSE);
                        std::cout << "defense " << my_chess[i].chessID << std::endl;
                    }
                }
                break;
            }
            case INTERFERE:{
                for(int i = 0; i < 16; i++) {
                    if(chessboard[i].color != side && (chessboard[i].currentCoor.region == OUTERLOOP ||
                                                       chessboard[i].currentCoor.region == TRACK) && chessboard[i].buff_state != DEFENSED) {
                        addMove(rollPoint, chessboard[i].chessID, INTERFERE);
                        std::cout << "interfere " <<chessboard[i].chessID << std::endl;
                    }
                }
                break;
            }
            case ELIMINATE:{
                for(int i = 0; i < 16; i++) {
                    if(chessboard[i].color == side && (chessboard[i].buff_state == DEFENSED || chessboard[i].buff_state == INTERFERED) ) {
                        addMove(rollPoint, chessboard[i].chessID, ELIMINATE);
                        std::cout << "eliminate "<< chessboard[i].chessID << std::endl;
                    }
                }
                break;
            }

            }
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

void moveGenerator::addMove(int rollPoint, int chessID, int aboutCard){
    moveList[moveCount].rollPoint = rollPoint;
    moveList[moveCount].chessID = chessID;
    moveList[moveCount].aboutCard = aboutCard;
    moveCount++;
    std::cout << moveCount << ": ";
}
