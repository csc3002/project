//
//  card_generator.h
//  Aeroplane_Project
//
//
//

#ifndef card_generator_h
#define card_generator_h

#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

class Card_Generator: public cocos2d::Sprite {
public:
	int roll;                                              // roll point
	int round;                                             // whose turn
	bool can_touch;                                        // enable to be touched or not

	virtual bool init();

	static Card_Generator* create();

	int getrandom();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	virtual void setTouchableFalse(EventCustom* event);

	virtual void setRollPoint(EventCustom* event);

	virtual void setRound(EventCustom* event);
};

#endif // card_generator_h
