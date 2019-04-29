//
//  card_generator.cpp
//  Aeroplane_Project
//
//  Created by Re-Entry on 2019/4/28.
//

#include "card_generator.h"
#include "random.h"
USING_NS_CC;

// initiate card generator
bool Card_Generator::init() {
    if (!Sprite::initWithFile("card_generator.png")) {
        return false;
    }
    setPosition(Vec2(900, 360));

    // set touch listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Card_Generator::onTouchBegan, this);
    touchListener->setSwallowTouches(true);

    // set custom event listeners
    auto rollPTListener = EventListenerCustom::create("roll_point", CC_CALLBACK_1(Card_Generator::setRollPoint, this));
    auto roundListener = EventListenerCustom::create("event_round", CC_CALLBACK_1(Card_Generator::setRound, this));
    auto planeClickListener = EventListenerCustom::create("plane_click", CC_CALLBACK_1(Card_Generator::setTouchableFalse, this));

    // add listeners to event dispactcher
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(rollPTListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(roundListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeClickListener, this);
    return true;
}

Card_Generator* Card_Generator::create() {
    Card_Generator* sprite = new Card_Generator();
    if (sprite->init()) {
        sprite->autorelease();
        sprite->roll = 0;
        sprite->round = 0;
        sprite->can_touch = false;
    }
    else {
        delete sprite;
        sprite = NULL;
        return NULL;
    }
    return sprite;
}

// get a random number (from 1 to 4) representing the card name
int Card_Generator::getrandom() {
    float num = randomInteger(1, 4);
    num = randomInteger(1, 4);
    num = 1; // implement 1 feature first
    return num;
}

bool Card_Generator::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 ptClick = touch->getLocation();
    if (this->getBoundingBox().containsPoint(ptClick) && can_touch) {
        int card_num = getrandom();
        can_touch = false;

        // pass the card number and player color to ALL card slots
        EventCustom eventClick = EventCustom("generator_click");
        int cardArray[2] = {card_num, round};
        eventClick.setUserData((int*)cardArray);
        _eventDispatcher->dispatchEvent(&eventClick);

        // getting a card consumes a move chance
        EventCustom eventPlaneClick = EventCustom("plane_click");
        eventPlaneClick.setUserData((bool*)false);
        _eventDispatcher->dispatchEvent(&eventPlaneClick);
        EventCustom eventPlaneEnd = EventCustom("plane_end");
        eventPlaneEnd.setUserData((bool*)true);
        _eventDispatcher->dispatchEvent(&eventPlaneEnd);
        return true;
    }
    return false;
}

// callback function to set the touchability to be false
void Card_Generator::setTouchableFalse(EventCustom* event) {
    can_touch = false;
}

// callback function to get the roll point and set the touchability
void Card_Generator::setRollPoint(EventCustom* event) {
    roll = *(int*)event->getUserData();
    if (roll == 1 || roll == 6) {
        can_touch = true;
    }
    else {
        can_touch = false;
    }
}

// callback function to get the round
void Card_Generator::setRound(EventCustom* event) {
    round = *(int*)event->getUserData();
}
