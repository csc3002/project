// TODO: file description

#include <iostream>
#include "searchengine.h"
#include "define.h"
#include "movegenerator.h"
#include "evaluator.h"

searchEngine::searchEngine()
{

}


searchEngine::~searchEngine(){
    delete pMG;
    delete pEval;
}

/*
 * Implementation note: play
 * --------------------------
 * TODO
 */

void searchEngine::play(CHESS chessboard[], int side){
    memcpy(cur_Chessboard, chessboard, sizeof(cur_Chessboard));     // copy the outer chessboard to the current one
    int rollCount = 0;      // count the times of rolling
    int count = 0;          // count the current number of moves
    while(rollCount < 3){   // dice can only be rolled 3 times
        rollPoint = pMG->roll();
        rollCount ++;
        if(rollCount == 3 && rollPoint == 6){   // rolling times check here
            count = 1;
            pMG->moveList[0].rollPoint = 6;
            pMG->moveList[0].chessID = ALLBACK;
        }
        else
            std::cout << "-------------------Adding moves-------------------" << std::endl;
            count = pMG->createPossibleMove(cur_Chessboard, rollPoint, side);
        if(count != 0){     // search move only when it is able to move a chess
            searchAGoodMove(count, side);
            makeMove(bestMove, cur_Chessboard, side);
        }
        if(!isGameOver(cur_Chessboard) && rollPoint == 6)   // if the game is not over and rolling point is 6, continue to roll
            continue;
        else
            break;
    }
    memcpy(chessboard, cur_Chessboard, sizeof(cur_Chessboard));     // copy the current chessboard to the outside
}

/*
 * Implementation note: searchAGoodMove
 * --------------------------
 * TODO
 */

void searchEngine::searchAGoodMove(int count, int side){
    int score = 0;
    int current = pEval->evaluate(cur_Chessboard, side);
    CHESS futureBoard[16];
    for(int i = 0; i < count ; i++){
        memcpy(futureBoard, cur_Chessboard, sizeof(cur_Chessboard));    // flush the future board every time
        makeMove(& pMG->moveList[i], futureBoard, side);
        score = pEval->evaluate(futureBoard, side);
        if(score >= current)        // if the future board is better than the current one, choose the move
            current = score;
            * bestMove = pMG->moveList[i];
    }
}

/*
 * Implementation note: makeMove
 * --------------------------
 * TODO
 */

void searchEngine::makeMove(CHESSMOVE * move, CHESS * chessboard,  int side){
    int head = -1;
    int tail = -1;
    int off = -1;
    int turn = -1;
    int flyBegin = -1;
    int flyEnd = -1;
    switch(side){
    case RED:{
        head = RED1;
        tail = RED4;
        off = RED_OFF;
        turn = RED_TURN;
        flyBegin = RED_FLY_BEGIN;
        flyEnd = RED_FLY_END;
        break;
    }

    case YELLOW:{
        head = YELLOW1;
        tail = YELLOW4;
        off = YELLOW_OFF;
        turn = YELLOW_TURN;
        flyBegin = YELLOW_FLY_BEGIN;
        flyEnd = YELLOW_FLY_END;
        break;
        }
    case BLUE:{
        head = BLUE1;
        tail = BLUE4;
        off = BLUE_OFF;
        turn = BLUE_TURN;
        flyBegin = BLUE_FLY_BEGIN;
        flyEnd = BLUE_FLY_END;
        break;
        }
    case GREEN:{
        head = GREEN1;
        tail = GREEN4;
        off = GREEN_OFF;
        turn = GREEN_TURN;
        flyBegin = GREEN_FLY_BEGIN;
        flyEnd = GREEN_FLY_END;
        break;
        }
    }
    int chessID = move->chessID;
    int rollPoint = move->rollPoint;

    if ( chessID == ALLBACK && rollPoint == 6)      // special treatment for the jinx case
        for(int i = head; i <= tail; i++){
            chessboard[i-1].currentCoor.region = APRON;
            chessboard[i-1].currentCoor.code = OUTSIDE;
        }
    else if (chessID == 0){     // if do not move, do not change the chessboard
        return ;
    }
    else{
        CHESS * nowChess;
        nowChess = &chessboard[chessID-1];              // find out the chess being moved
        if(nowChess->currentCoor.region == APRON)       // special treatement for taking off
            nowChess->currentCoor.region = OFF;
        else{
            if(nowChess->currentCoor.code == turn || nowChess->currentCoor.region == TRACK)
                genInnerMove(nowChess, chessboard, rollPoint,turn);     // change the chessboard

            else
                genOuterMove(nowChess, chessboard,side, rollPoint, off, turn, flyBegin, flyEnd); // change the chessboard

        }
    }
}

/*
 * Implementation note: isGameOver
 * ---------------------------------
 *
 */

bool searchEngine::isGameOver(const CHESS chessboard[]){
    bool redWin = (chessboard[0].currentCoor.region == WIN || chessboard[1].currentCoor.region == WIN ||
                   chessboard[2].currentCoor.region == WIN || chessboard[3].currentCoor.region == WIN);
    bool yellowWin = (chessboard[4].currentCoor.region == WIN || chessboard[5].currentCoor.region == WIN ||
                   chessboard[6].currentCoor.region == WIN || chessboard[7].currentCoor.region == WIN);
    bool blueWin = (chessboard[8].currentCoor.region == WIN || chessboard[9].currentCoor.region == WIN ||
                   chessboard[10].currentCoor.region == WIN || chessboard[11].currentCoor.region == WIN);
    bool greenWin = (chessboard[12].currentCoor.region == WIN || chessboard[13].currentCoor.region == WIN ||
                   chessboard[14].currentCoor.region == WIN || chessboard[15].currentCoor.region == WIN);
    return (redWin || yellowWin || blueWin || greenWin);
}


/*
 * Implementation note: genOuterMove
 * ---------------------------------
 *
 */

void searchEngine::genOuterMove(CHESS * chess, CHESS * chessboard, int side, int rollPoint, int off, int turn, int flyBegin, int flyEnd){
    int n = chess->currentCoor.code ;      // code of the destination
    if(chess->currentCoor.region == OFF) {             // if starts from taking off point, use special treatment
        n = off + rollPoint -1;
        chess->currentCoor.region = OUTERLOOP;
    }
    else{
        if ((turn - n + 52) % 52 <= rollPoint){           // if roll point is larger than the distance to turn point,
            int rest = rollPoint - (turn - n + 52) % 52;  // use special treatment
            if(rest == 0){                                // go to the turn point
                n = turn;
                chess->currentCoor.code = n;
                for(int i = 0; i < 16; i++){             // crash other plan if needed
                    if(chessboard[i].color != side && chessboard[i].currentCoor.code == n)
                        chessboard[i].currentCoor.region = APRON;
                        chessboard[i].currentCoor.code = OUTSIDE;
                }
                return ;
            }
            else{                                       // go to the track
                n = rest;
                chess->currentCoor.region = TRACK;
                chess->currentCoor.code = n;
                return ;
            }

        }
        else
            n = (n + rollPoint) % 52;       // if starts from outerloop point not close to turn point,
                                            // generate potential destination code
    }

    if(n % 4 != side){                      // if can't jump or fly, just change the chessboard
        chess->currentCoor.code = n;
        for(int i = 0; i < 16; i++){             // crash other plan if needed
            if(chessboard[i].color != side && chessboard[i].currentCoor.code == n)
                chessboard[i].currentCoor.region = APRON;
                chessboard[i].currentCoor.code = OUTSIDE;
        }
        return ;
    }
    else{
        if(n == flyBegin){                  // if goes to the fly begin at first, directly go to
            n = flyEnd + 4;                // 4 blocks after the fly end
            chess->currentCoor.code = n;
            for(int i = 0; i < 16; i++){             // crash other plan if needed
                if(chessboard[i].color != side && chessboard[i].currentCoor.code == n)
                    chessboard[i].currentCoor.region = APRON;
                    chessboard[i].currentCoor.code = OUTSIDE;
            }
            return ;
        }
        else{
            n = (n+4) % 52;
            if(n == flyBegin){              // if jump to the fly begin, go to the fly end and stop
                n = flyEnd;
                chess->currentCoor.code = n;
                for(int i = 0; i < 16; i++){             // crash other plan if needed
                    if(chessboard[i].color != side && chessboard[i].currentCoor.code == n)
                        chessboard[i].currentCoor.region = APRON;
                        chessboard[i].currentCoor.code = OUTSIDE;
                }
                return ;
            }
            else{
                chess->currentCoor.code = n;
                for(int i = 0; i < 16; i++){             // crash other plan if needed
                    if(chessboard[i].color != side && chessboard[i].currentCoor.code == n)
                        chessboard[i].currentCoor.region = APRON;
                        chessboard[i].currentCoor.code = OUTSIDE;
                }
                return ;
            }
        }
    }
}

/*
 * Implementation note: genInnerMove
 * ---------------------------------
 *
 */

void searchEngine::genInnerMove(CHESS * chess, CHESS * chessboard, int rollPoint, int turn){
    int n = chess->currentCoor.code ;      // code of the destination
    if(n == turn){
        if(rollPoint == 6){                // go 6 blocks from turn point can win
            chess->currentCoor.region = WIN;
            chess->currentCoor.code = OUTSIDE;
            return;
        }
        else{                            // go from turn point to other track point
            n = rollPoint;
            chess->currentCoor.code = n;
            return ;
        }
    }
    else{
        n = n + rollPoint;
        if(n < 6){
            chess->currentCoor.code = n;
            return ;
        }
        else if(n == 6){
            chess->currentCoor.region = WIN;
            chess->currentCoor.code = OUTSIDE;
            return;
        }
        else{
            n = 12 - n;
            chess->currentCoor.code = n;
            return ;
        }
    }
}
