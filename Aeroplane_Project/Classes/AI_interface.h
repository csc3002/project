#pragma once
#ifndef AI_interface_h
#define AI_interface_h

#include "cocos2d.h"
#include "define.h"
#include "searchengin.h"
USING_NS_CC;

class AI_player: public searchEngine, public Node {
public:
    bool init();
    static AI_player* create();
    CHESS chessboard[16];
    int side;

    void saveChessboard(EventCustom* event);

    void savePoint(EventCustom* event);

    void saveCard(EventCustom* event);

    void AIPlay();
};

#endif // AI_interface_h
