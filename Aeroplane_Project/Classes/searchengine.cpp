/*
 * File: simplesearchengine.cpp
 * ----------------------------
 * This file is the implementatio of search engine.
 */

#include <iostream>
#include "searchengin.h"
#include "define.h"
#include "movegenerator.h"
#include "evaluator.h"

/* costructor and destructor */
searchEngine::searchEngine()
{

}

// destructor should remove the move generator and evaluator
searchEngine::~searchEngine()
{

}

/*
 * Implementation note: play
 * --------------------------
 * This method simulates player behavior like this:
 * 1. Copy the chessboard into cur_Chessboard which is inside the search engine instance;
 * 2. Roll the dice. Then take create move.
 * 3. If there is only one move, it must be "not possible to move" case. Then do not do any movement.
 *    If there is more than one possible move, search a good move and make move.
 * 4. If game is not over and roll point is six, continue until the third time roll. Else, player end its turn.
 * 5. Copy the modified chessboard in place to the original one.
 */

void searchEngine::play(CHESS chessboard[], int side){
    if(isGameOver(chessboard)){
        return ;
    }
    memcpy(cur_Chessboard, chessboard, sizeof(cur_Chessboard));     // copy the outer chessboard to the current one
    //int rollCount = 0;      // count the times of rolling
    int count = 0;          // count the current number of moves
    while(true){   // dice can be rolled n times if keep rolling out 6
        this->rollPoint = pMG->roll();
        //rollCount ++;
          std::cout << "-------------------Adding moves-------------------" << std::endl;
        count = pMG->createPossibleMove(cur_Chessboard, this->rollPoint, side, myCard);

        if(count != 1){     // search move only when it is able to move a chess
            searchAGoodMove(count, side, myCard);
            std::cout << "Current best move: " << bestMove->chessID << " , "<< bestMove->rollPoint << " , " << bestMove->aboutCard << std::endl;

            if(bestMove->aboutCard == DRAW) {
                myCard = rand() % 4 + 1;
            }
            else if (bestMove->aboutCard != NOCARD) {
                useAbility(bestMove, cur_Chessboard, side);
                myCard = NOCARD;
                break;
            }
            else if (bestMove->aboutCard == NOCARD){
                makeMove(bestMove, cur_Chessboard, side);
            }
        }

        if(!isGameOver(cur_Chessboard) && this->rollPoint == 6)   // if the game is not over and rolling point is 6, continue to roll
            continue;
        else
            break;
        }
    memcpy(chessboard, cur_Chessboard, sizeof(cur_Chessboard));     // copy the current chessboard to the outside
}

/*
 * Implementation note: searchAGoodMove
 * --------------------------
 * The AI search a good move like this:
 * 1. Set the current best move to the first element in moveList.
 * 2. Iterate through the possible move, generate a future board for each of them
 * 3. Evaluate the current chessboard and every future board's value.
 * 4. Compare each value, and set bestMove to the move which has the largest value.
 */

void searchEngine::searchAGoodMove(int count, int side, int hadCard){
    int score = 0;
    int current = 0;
    bestMove = & pMG->moveList[0];

    CHESS futureBoard[16];
    for(int i = 1; i < count ; i++){
        memcpy(futureBoard, cur_Chessboard, sizeof(cur_Chessboard));    // flush the future board every time
        if(pMG->moveList[i].aboutCard == DRAW) {                        // special treatment of drawing card
            if(hadCard == NOCARD)
                score = 500;
            else{
                int a = rand() % 6 + 1;
                if(hadCard == ATTACK)
                    score = 120 * a;
                else if(a <=2)
                    score = 20;
                else
                    score = 90 * a;
            }
        }
        else if(pMG->moveList[i].aboutCard != NOCARD) {         // special treatment for using abilities
            useAbility(& pMG->moveList[i], futureBoard, side);
            score = pEval->evaluate(cur_Chessboard, futureBoard, side);
        }
        else if(pMG->moveList[i].aboutCard == NOCARD) {        // treatment for moving chess
            makeMove(& pMG->moveList[i], futureBoard, side);
            score = pEval->evaluate(cur_Chessboard, futureBoard, side);
        }
        std::cout << "Score: " << score << std::endl;
        if(score >= current){         // if the future board is better than the current one, choose the move
            current = score;
            bestMove = & pMG->moveList[i];
        }
    }
}

/*
 * Implementation note: makeMove
 * --------------------------
 * This method work like this:
 * 1. Set some critical points(turning points, flying points, etc.) according to the side;
 * 2. Handle the taking off case;
 * 3. If not taking off, handle normal move case. If the chess is about or is right in track,
 *    use inner move function; else, use outer move function.
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

    if (chessID == 0 || chessboard[chessID-1].buff_state == INTERFERED){     // if do not move, do not change the chessboard
        return ;
    }
    else{                       // else, move chess
        CHESS * nowChess;
        nowChess = &chessboard[chessID-1];              // find out the chess being moved
        if(nowChess->currentCoor.region == APRON)   {   // special treatement for taking off
            nowChess->currentCoor.region = OFF;
        }
        else{
            if(nowChess->currentCoor.code == turn || nowChess->currentCoor.region == TRACK)
                genInnerMove(nowChess, rollPoint,turn);     // change the chessboard

            else
                genOuterMove(nowChess, chessboard,side, rollPoint, off, turn, flyBegin, flyEnd); // change the chessboard

        }
    }
}

/*
 * Implementation note: useAbility
 * ---------------------------------
 * There are 4 kinds of ability:
 * 1. Attack: selecting one of OWN chess on outerloop, enemy chesses which located within 3 blocks away will be crashed.
 * 2. Defense: selecting one of OWN chess, this chess will not be attack or interfere in 5 rounds.
 * 3. Interfere: selecting one enemy chess, this chess cannot move in 4 rounds.
 * 4. Eliminate: selectiong one of own chess or enemy chess, the defensed/interfered state will be eliminate.
 */

void searchEngine::useAbility(CHESSMOVE * move, CHESS * chessboard,  int side) {
    int ability = move->aboutCard;
    int myLocation = chessboard[move->chessID-1].currentCoor.code;
    int enemyLocation;
    switch (ability) {
    case ATTACK:{
        for(int i = 0; i < 16; i++){
            enemyLocation = chessboard[i].currentCoor.code;
            if(chessboard[i].color != side && chessboard[i].currentCoor.region == OUTERLOOP &&
               chessboard[i].buff_state != DEFENSED && ((myLocation + 52 - enemyLocation )% 52 <= 5 || (enemyLocation + 52 - myLocation )% 52 <= 5)) {
                chessboard[i].currentCoor.region = APRON;
                chessboard[i].currentCoor.code = OUTSIDE;
				chessboard[i].buff_state = NONE;
                chessboard[i].round_left = 0;
                std::cout << "chess being attacked: " << chessboard[i].chessID << std::endl;
            }
        }
        break;
    }
    case DEFENSE: {
        chessboard[move->chessID-1].buff_state = DEFENSED;
        chessboard[move->chessID-1].round_left += 20;
        break;
    }
    case INTERFERE: {
        chessboard[move->chessID-1].buff_state = INTERFERED;
        chessboard[move->chessID-1].round_left += 16;
        break;
    }
    case ELIMINATE: {
        chessboard[move->chessID-1].buff_state = NONE;
        chessboard[move->chessID-1].round_left = 0;
        break;
    }
    }
}

/*
 * Implementation note: isGameOver
 * ---------------------------------
 * This function iterate through the chessboard. If 4 chesses of the same color are set to win,
 * then the game is over.
 */

bool searchEngine::isGameOver(const CHESS chessboard[]){
    bool redWin = (chessboard[0].currentCoor.region == WIN && chessboard[1].currentCoor.region == WIN &&
                   chessboard[2].currentCoor.region == WIN && chessboard[3].currentCoor.region == WIN);
    bool yellowWin = (chessboard[4].currentCoor.region == WIN && chessboard[5].currentCoor.region == WIN &&
                   chessboard[6].currentCoor.region == WIN && chessboard[7].currentCoor.region == WIN);
    bool blueWin = (chessboard[8].currentCoor.region == WIN && chessboard[9].currentCoor.region == WIN &&
                   chessboard[10].currentCoor.region == WIN && chessboard[11].currentCoor.region == WIN);
    bool greenWin = (chessboard[12].currentCoor.region == WIN && chessboard[13].currentCoor.region == WIN &&
                   chessboard[14].currentCoor.region == WIN && chessboard[15].currentCoor.region == WIN);
    return (redWin || yellowWin || blueWin || greenWin);
}

/*
 * Implementation note: genOuterMove
 * ---------------------------------
 * This function generate moves if the chess is on the taking off state or on outerloop bu not at
 * the turning point. It works like this:
 * 1. If the chess is on taking off state, generate temporary destination specially;
 * 2. If the chess is about to enter the inner loop, just go; otherwise generate temporary destination normally;
 * 3. Check the temporary destination:
 *    3.1. If the temporary destination is not the same color, do move and end the function;
 *    3.2. When the temporary destination is the same color, do jump or fly.
 *    3.3 After jump or fly, check if can jump again. If no, do move and end the function; if yes, jump again and
 *        do move and end the function.
 */

void searchEngine::genOuterMove(CHESS * chess, CHESS * chessboard, int side, int rollPoint, int off, int turn, int flyBegin, int flyEnd){
    int n = chess->currentCoor.code ;      // code of the destination
    if(chess->currentCoor.region == OFF) {             // if starts from taking off point, use special treatment
        n = off + rollPoint -1;
        chess->currentCoor.region = OUTERLOOP;
    }
    else if(n >= 0){                        // make sure the plane is on outer loop
        if ((turn - n + 52) % 52 <= rollPoint){           // if roll point is larger than the distance to turn point,
            int rest = rollPoint - (turn - n + 52) % 52;  // use special treatment
            if(rest == 0){                                // go to the turn point
                n = turn;
                chess->currentCoor.code = n;
                for(int i = 0; i < 16; i++){             // crash other plan if needed
                    if(chessboard[i].color != side && chessboard[i].currentCoor.region == OUTERLOOP && chessboard[i].currentCoor.code == n){
                        chessboard[i].currentCoor.region = APRON;
                        chessboard[i].currentCoor.code = OUTSIDE;
                    }
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
            if(chessboard[i].color != side && chessboard[i].currentCoor.region == OUTERLOOP &&chessboard[i].currentCoor.code == n){
                chessboard[i].currentCoor.region = APRON;
                chessboard[i].currentCoor.code = OUTSIDE;
            }
        }
        return ;
    }
    else{
        if(n == flyBegin){                  // if goes to the fly begin at first, directly go to
            n = flyEnd + 4;                // 4 blocks after the fly end
            chess->currentCoor.code = n;
            for(int i = 0; i < 16; i++){             // crash other plan if needed
                if(chessboard[i].color != side && chessboard[i].currentCoor.region == OUTERLOOP &&chessboard[i].currentCoor.code == n){
                    chessboard[i].currentCoor.region = APRON;
                    chessboard[i].currentCoor.code = OUTSIDE;
                }
            }
            return ;
        }
        else{
            n = (n+4) % 52;
            if(n == flyBegin){              // if jump to the fly begin, go to the fly end and stop
                n = flyEnd;
                chess->currentCoor.code = n;
                for(int i = 0; i < 16; i++){             // crash other plan if needed
                    if(chessboard[i].color != side && chessboard[i].currentCoor.region == OUTERLOOP &&chessboard[i].currentCoor.code == n){
                        chessboard[i].currentCoor.region = APRON;
                        chessboard[i].currentCoor.code = OUTSIDE;
                    }
                }
                return ;
            }
            else{
                chess->currentCoor.code = n;
                for(int i = 0; i < 16; i++){             // crash other plan if needed
                    if(chessboard[i].color != side && chessboard[i].currentCoor.region == OUTERLOOP &&chessboard[i].currentCoor.code == n){
                        chessboard[i].currentCoor.region = APRON;
                        chessboard[i].currentCoor.code = OUTSIDE;
                    }
                }
                return ;
            }
        }
    }
}

/*
 * Implementation note: genInnerMove
 * ---------------------------------
 * This function generate moves if the chess is at the turning point or on the track. It works
 * like this:
 * 1. If chess is at the turning point, use special movement;
 * 2. If the chess is on the track, use normal movement:
 *    2.1. If the roll point can't make the chess to the win point, just move;
 *    2.2. If the roll point can make the chess to the win point, set the chess to win state;
 *    2.3. If the roll point exceed, let the chess go forward and go backward accordingly.
 */

void searchEngine::genInnerMove(CHESS * chess, int rollPoint, int turn){
    chess->currentCoor.region = TRACK;      // change the region to track if initially at the turn point
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
