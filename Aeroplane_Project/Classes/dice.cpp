//
//  dice.cpp
//  Aeroplane_Project
//
//  Created by HRBattery on 2019/4/22.
//  Modified by Re-Entry

#include "dice.h"
#include "random.h"
USING_NS_CC;

// initiate dice
bool Dice::init() {
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
    auto planeStatusListener = EventListenerCustom::create("plane_status", CC_CALLBACK_1(Dice::setStatusArray, this));
    //auto cardListener = EventListenerCustom::create("use_card", CC_CALLBACK_1(Dice::skipTurn, this));

    // add listeners to event dispactcher
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeEndListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeStatusListener, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(cardListener, this);
    return true;
}

Dice* Dice::create(int player0, int player1, int player2, int player3) {
    Dice* sprite = new Dice();
    if (sprite->init()) {
        sprite->autorelease();
        sprite->roll_num = 0;
        sprite->round = 0;
        sprite->can_touch = true;
        sprite->playerArray[0] = player0;
        sprite->playerArray[1] = player1;
        sprite->playerArray[2] = player2;
        sprite->playerArray[3] = player3;
    }
    else {
        delete sprite;
        sprite = NULL;
        return NULL;
    }
    return sprite;
}

// get a random number as roll point
int Dice::getrandom() {
    float roll_num = randomInteger(1, 6);
    roll_num = randomInteger(1, 6);
    if (roll_num == 1) {
        this->setTexture("dice1.png");
    }
    else if(roll_num == 2) {
        this->setTexture("dice2.png");
    }
    else if (roll_num == 3) {
        this->setTexture("dice3.png");
    }
    else if (roll_num == 4) {
        this->setTexture("dice4.png");
    }
    else if (roll_num == 5) {
        this->setTexture("dice5.png");
    }
    else if (roll_num == 6) {
        this->setTexture("dice6.png");
    }
    return roll_num;
}

bool Dice::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 ptClick = touch->getLocation();
    if (this->getBoundingBox().containsPoint(ptClick) && can_touch) {

        // skip if the player is nobody
        while (!playerArray[round]) {
            round = (round + 1) % 4;
        }

        roll_num = getrandom();
        can_touch = false;

        // pass touchable to corresponding planes
        EventCustom eventClick = EventCustom("roll_click_blue");
        switch (round) {
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
        _eventDispatcher->dispatchEvent(&eventClick);

        // pass roll point to ALL planes
        EventCustom eventRollPT = EventCustom("roll_point");
        eventRollPT.setUserData((void*)&roll_num);
        _eventDispatcher->dispatchEvent(&eventRollPT);

        // pass round to the card generator
        EventCustom eventRound = EventCustom("event_round");
        eventRound.setUserData((void*)&round);
        _eventDispatcher->dispatchEvent(&eventRound);

        // if roll_num is not 6, the next player rolls the dice
        if (roll_num != 6) {
            round = (round + 1) % 4;
        }
        return true;
    }
    return false;
}

// callback function to set the touchability of dice
void Dice::setTouchable(EventCustom* event) {
    can_touch = (bool*)event->getUserData();
}

// callback function to set the status array of corresponding color
void Dice::setStatusArray(EventCustom* event) {
    int* array = (int*)event->getUserData();
    statusArray[*(array + 1)] = *array;

    // if all the planes of corresponding color are untouchable, skip the color and reset the touchablity of dice
    if (!(statusArray[0] || statusArray[1] || statusArray[2] || statusArray[3])) {
        can_touch = true;
    }
    else {
        can_touch = false;
    }
}

// callback function to skip a player if the card_generator is clicked
void Dice::skipTurn(EventCustom* event) {
    round = (round + 1) % 4;
    can_touch = true;
}
