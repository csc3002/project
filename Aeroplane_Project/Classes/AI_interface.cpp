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
    auto cardListener = EventListenerCustom::create("event_receive_card", CC_CALLBACK_1(AI_player::saveCard, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(chessboardListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(pointListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(cardListener, this);
    return true;
}

AI_player* AI_player::create() {
    AI_player* sprite = new AI_player();
    if (sprite->init()) {
        sprite->autorelease();
    }
    else {
        delete sprite;
        sprite = NULL;
        return NULL;
    }
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
    rollPoint = array[0];
    side = (array[1] + 2) % 4;
    log("save point");
    AIPlay();
}

void AI_player::saveCard(EventCustom* event) {
    int card_num = *(int*)event->getUserData();
    myCard = card_num;
    if (myCard == 0) {myCard = -1;}
    log("save card");
}

void AI_player::AIPlay() {
    if(isGameOver(chessboard)) {
        return;
    }
    int count = 0;          // count the current number of moves
    memcpy(cur_Chessboard, chessboard, sizeof(cur_Chessboard));
    log("rollPoint %d side %d myCard %d", rollPoint, side, myCard);
    count = pMG->createPossibleMove(chessboard, rollPoint, side, myCard);
    if (count == 1) {
        log("ai nomove");
        EventCustom eventAINoMove = EventCustom("AI_NoMove");
        _eventDispatcher->dispatchEvent(&eventAINoMove);
        return;
    }
    else {     // search move only when it is able to move a chess
        searchAGoodMove(count, side, myCard);
    }
    if (bestMove->aboutCard == DRAW) {
        log("ai draw");
        EventCustom eventAIDraw = EventCustom("AI_Draw");
        _eventDispatcher->dispatchEvent(&eventAIDraw);
    }
    else if (bestMove->aboutCard != NOCARD) {
        log("ai usecard");
        EventCustom eventAIUseCard = EventCustom("AI_UseCard");
        eventAIUseCard.setUserData((int*)&(bestMove->chessID));
        _eventDispatcher->dispatchEvent(&eventAIUseCard);
    }
    else if (bestMove->aboutCard == NOCARD) {
        log("ai move");
        log("chessid %d rollpoint %d aboutcard %d", bestMove->chessID, bestMove->rollPoint, bestMove->aboutCard);
        EventCustom eventAIMove = EventCustom("AI_Move");
        eventAIMove.setUserData((int*)&(bestMove->chessID));
        _eventDispatcher->dispatchEvent(&eventAIMove);
    }
}
