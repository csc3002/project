#include "AI_interface.h"
#include "cocos2d.h"
#include "define.h"
#include "movegenerator.h"
#include "searchengin.h"
#include "evaluator.h"
#include "planes.h"
#include "dice.h"

USING_NS_CC;

bool AI_player::init() {
    auto chessboardListener = EventListenerCustom::create("event_receive_chessboard", CC_CALLBACK_1(AI_player::saveChessboard, this));
    auto pointListener = EventListenerCustom::create("event_receive_point", CC_CALLBACK_1(AI_player::savePoint, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(chessboardListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(pointListener, this);
    return true;
}
AI_player* AI_player::create() {
    AI_player* sprite = new AI_player();
    if (sprite->init())
    return sprite;
}

void AI_player::saveChessboard(EventCustom* event) {
    CHESS* array = (CHESS*)event->getUserData();
    for (int i=0; i<16; ++i) {
        chessboard[i] = array[i];
    }
    log("save chessboard");
}

void AI_player::savePoint(EventCustom* event) {
    int* array = (int*)event->getUserData();
    roll_num = array[0];
    round = array[1];
    side = (round + 2) % 4;
    log("save point");
    AI_player::AIPlay();
}

void AI_player::AIPlay() {
    if(isGameOver(chessboard)){
        return;
    }
    int count = 0;          // count the current number of moves
    count = pMG->createPossibleMove(chessboard, roll_num, side, myCard);
    if(count != 1){     // search move only when it is able to move a chess
        searchAGoodMove(count, side, myCard);
    }
    
}


