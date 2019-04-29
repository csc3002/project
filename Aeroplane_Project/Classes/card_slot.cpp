//
//  card_generator.cpp
//  Aeroplane_Project
//
//  Created by Re-Entry on 2019/4/28.
//

#include "card_slot.h"
USING_NS_CC;

// initiate card slot
bool Card_Slot::init() {
    if (!Sprite::initWithFile("none.png")) {
        return false;
    }

    // set touch listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Card_Slot::onTouchBegan, this);
    touchListener->setSwallowTouches(true);

    // set custom event listeners

    // add listeners to event dispactcher
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}

Card_Slot* Card_Slot::create(int _color, int _player_count) {
    Card_Slot* sprite = new Card_Slot();
    if (sprite->init()) {
        sprite->autorelease();
        sprite->color = _color;
        sprite->card_num = 0;
        sprite->player_count = _player_count;
        sprite->can_touch = false;
    }
    else {
        delete sprite;
        sprite = NULL;
        return NULL;
    }
    return sprite;
}

bool Card_Slot::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 ptClick = touch->getLocation();
    if (this->getBoundingBox().containsPoint(ptClick) && can_touch && card_num) {
        cocos2d::log("%d", color);
        return true;
    }
    return false;
}
