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

// initial dice
bool Dice::init(){
    if (!Sprite::initWithFile("dice.png")) {
        return false;
    }
    setPosition(Vec2(900, 600));
    // set touch listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Dice::onTouchBegan, this);
    touchListener->setSwallowTouches(true);
    // set custom event listeners
    auto planeEndListener = EventListenerCustom::create("plane_end", CC_CALLBACK_1(Dice::setTouchable, this));
    auto planeStatusListener_0 = EventListenerCustom::create("plane_status_0", CC_CALLBACK_1(Dice::setStatusArray, this));
    auto planeStatusListener_1 = EventListenerCustom::create("plane_status_1", CC_CALLBACK_1(Dice::setStatusArray, this));
    auto planeStatusListener_2 = EventListenerCustom::create("plane_status_2", CC_CALLBACK_1(Dice::setStatusArray, this));
    auto planeStatusListener_3 = EventListenerCustom::create("plane_status_3", CC_CALLBACK_1(Dice::setStatusArray, this));
    // add listeners to event dispactcher
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeEndListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeStatusListener_0, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeStatusListener_1, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeStatusListener_2, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeStatusListener_3, this);
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

// get random numbers as roll point
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
        // pass touchable to corresponding planes
        EventCustom eventClick = EventCustom("roll_click_blue");
        switch (this->round) {
            case 0: // case blue
                eventClick = EventCustom("roll_click_blue");
                break;
            case 1: // case green
                eventClick = EventCustom("roll_click_green");
                break;
            case 2: // case red
                eventClick = EventCustom("roll_click_red");
                break;
            case 3: // case yellow
                eventClick = EventCustom("roll_click_yellow");
                break;
        }
        eventClick.setUserData((void*)true);
        // pass roll point to all planes
        EventCustom eventRollPT = EventCustom("roll_point");
        eventRollPT.setUserData((void*)&roll_num);
        _eventDispatcher->dispatchEvent(&eventClick);
        _eventDispatcher->dispatchEvent(&eventRollPT);
        // if roll_num != 6, the next player roll the dice
        if (roll_num != 6) {
            round = (round + 1) % 4;
        }
        // if all the planes of corresponding color are untouchable, skip the color and reset the touchablity of dice
        if (!statusArray[0] || statusArray[1] || statusArray[2] || statusArray[3]){
            can_touch = true;
        }
    }
    return true;
}

// callback function to set the touchability of dice
void Dice::setTouchable(EventCustom* event){
    can_touch = (bool*)event->getUserData();
}

// callback function to set the status array of corresponding color
void Dice::setStatusArray(EventCustom* event){
    int* array = (int*)event->getUserData();
    statusArray[*(array+1)] = *array;
}
