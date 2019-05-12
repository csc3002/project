//
//  card_slot_animation.h
//  Aeroplane_Project
//
//  Created by Re-Entry on 2019/5/12.
//

#ifndef card_slot_animation_h
#define card_slot_animation_h

#include "cocos2d.h"
USING_NS_CC;

class Card_Slot_Animation: public cocos2d::Sprite {
public:

    virtual bool init();

    static Card_Slot_Animation* create();

    virtual void play_animation(EventCustom* event);

};

#endif // card_slot_animation_h
