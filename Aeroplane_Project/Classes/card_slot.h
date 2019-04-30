//
//  card_generator.h
//  Aeroplane_Project
//
//  Created by Re-Entry on 2019/4/28.
//

#ifndef card_slot_h
#define card_slot_h

#include "cocos2d.h"
USING_NS_CC;

class Card_Slot: public cocos2d::Sprite {
public:
    int color;                                             // 0 = blue, 1 = green, 2 = red, 3 = yellow
    int card_num;                                          // the kind of the card stored, 0 = none, 1 = machinegun, 2 = protection, 3 = stopaction, 4 = neutralize
    int player_count;                                      // the number of players
    bool can_touch;                                        // enable to be touched or not

    virtual bool init();

    static Card_Slot* create(int _color, int _player_count);

    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

    virtual void setCard(EventCustom* event);

    virtual void setTouchable(EventCustom* event);

    virtual void setTouchableFalse(EventCustom* event);
};

#endif // card_slot_h
