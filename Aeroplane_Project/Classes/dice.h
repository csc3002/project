//
//  dice.hpp
//  Aeroplane_Project
//
//  Created by HRBattery on 2019/4/22.
//

#ifndef dice_h
#define dice_h

#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

class Dice: public cocos2d::Sprite{
    public:
    int roll_num;
    bool can_touch;
    
    virtual bool init();
    
    static Dice* create();
    
    int getrandom();
    
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    
    virtual void setTouchable(EventCustom* event);
};
#include <stdio.h>

#endif /* dice_h */
