#pragma once
#ifndef AI_interface_h
#define AI_interface_h
#include "cocos2d.h"
#include <string>
#include "define.h"
#include "searchengin.h"
USING_NS_CC;

class AI_player: public searchEngine, public Node{
public:
    void create();
    CHESS chessboard[16];
    int roll_num;
    int round;
    int side;

    void saveChessboard(EventCustom* event);
    
    void savePoint(EventCustom* event);
    
    void AIPlay();
};
#endif
