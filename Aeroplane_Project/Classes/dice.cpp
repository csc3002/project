//
//  dice.cpp
//  Aeroplane_Project
//
//  Created by HRBattery on 2019/4/22.
//

#include "dice.h"
#include <string>
USING_NS_CC;
using namespace std;

bool Dice::init(){
    if (!Sprite::initWithFile("dice.png")) {
        return false;
    }
//    setScale(0.095f, 0.095f);
    setPosition(Vec2(900, 600));
    auto touchListener = EventListenerTouchOneByOne::create();
    auto planeEndListener = EventListenerCustom::create("plane_end", CC_CALLBACK_1(Dice::setTouchable, this));
    touchListener->onTouchBegan = CC_CALLBACK_2(Dice::onTouchBegan, this);
    touchListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeEndListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}

Dice* Dice::create(){
    Dice* sprite = new Dice();
    if (sprite->init()){
        sprite->autorelease();
        sprite->roll_num = 0;
        sprite->can_touch = true;
    }
    else {
        delete sprite;
        sprite = NULL;
        return NULL;
    }
    return sprite;
}

int Dice::getrandom(){
    float ran = CCRANDOM_0_1();
    if (ran <= 0.166){
        roll_num = 1;
        this->setTexture("dice1.png");
    }
    else if(0.166 < ran <= 0.333){
        roll_num = 2;
        this->setTexture("dice2.png");
    }
    else if (0.333 < ran <= 0.5) {
        roll_num = 3;
        this->setTexture("dice3.png");
    }
    else if (0.5 < ran <= 0.666) {
        roll_num = 4;
        this->setTexture("dice4.png");
    }
    else if (0.666 < ran <= 0.833) {
        roll_num = 5;
        this->setTexture("dice5.png");
    }
    else if (0.833 < ran < 1) {
        roll_num = 6;
        this->setTexture("dice6.png");
    }
    return roll_num;
}

bool Dice::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
    Vec2 ptClick = touch->getLocation();
    if (this->getBoundingBox().containsPoint(ptClick) && can_touch){
        roll_num = this->getrandom();
        can_touch = false;
        EventCustom eventClick = EventCustom("roll_click");
        eventClick.setUserData((void*)true);
        EventCustom eventRollPT = EventCustom("roll_point");
        eventRollPT.setUserData((void*)&roll_num);
        _eventDispatcher->dispatchEvent(&eventClick);
        _eventDispatcher->dispatchEvent(&eventRollPT);
    }
    return true;
}

void Dice::setTouchable(EventCustom* event){
    can_touch = (bool*)event->getUserData();
}
