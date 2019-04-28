//
//  card_generator.h
//  Aeroplane_Project
//
//  Created by Re-Entry on 2019/4/28.
//

#ifndef card_slot_h
#define card_slot_h

#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

class Card_Slot: public cocos2d::Sprite {
public:
	int color;                                             // 0 = blue, 1 = green, 2 = red, 3 = yellow
	bool can_touch;                                        // enable to be touched or not
	string card_name;                                      // the name of the card stored

	virtual bool init();

	static Card_Slot* create();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	virtual void setTouchable(EventCustom* event);
};

#endif // card_slot_h
