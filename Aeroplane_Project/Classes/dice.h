//
//  dice.hpp
//  Aeroplane_Project
//
//  Created by HRBattery on 2019/4/22.
//  Modified by Re-Entry

#ifndef dice_h
#define dice_h

#include "cocos2d.h"
#include "define.h"
USING_NS_CC;

class Dice: public cocos2d::Sprite{
public:
    int roll_num;
    int round;
    bool can_touch;
    Sprite* sign;
    int updated_num;
    int statusArray[4];
    int playerArray[4];
    CHESS chessboard[16];

    virtual bool init();

    static Dice* create(int player0, int player1, int player2, int player3);

    int getrandom();

    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

    virtual void setTouchable(EventCustom* event);

    virtual void setTouchableFalse(EventCustom* event);

    virtual void setStatusArray(EventCustom* event);

    virtual void skipTurn(EventCustom* event);

    virtual void AICall();

    virtual void AIPass(EventCustom* event);
    
    virtual void cardPass(EventCustom* event);

private:
    int chessboardStatus = 0;
};

#endif // dice_h
