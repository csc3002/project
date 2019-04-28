//
//  dice.hpp
//  Aeroplane_Project
//
//  Created by HRBattery on 2019/4/22.
//  Modified by Re-Entry

#ifndef dice_h
#define dice_h

#include "cocos2d.h"
USING_NS_CC;

class Dice: public cocos2d::Sprite{
public:
    int roll_num;
    bool can_touch;
    int round;
    int statusArray[4];
	int playerArray[4];
    
    virtual bool init();
    
    static Dice* create(int player0, int player1, int player2, int player3);
    
    int getrandom();
    
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    
    virtual void setTouchable(EventCustom* event);
    
    virtual void setStatusArray(EventCustom* event);
    
    virtual void skipTurn(EventCustom* event);
};

#endif // dice_h
