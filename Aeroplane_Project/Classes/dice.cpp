//
//  dice.cpp
//  Aeroplane_Project
//
//  Created by HRBattery on 2019/4/22.
//  Modified by Re-Entry

#include "dice.h"
#include "random.h"
USING_NS_CC;

// initiate the dice
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
    auto slotListener = EventListenerCustom::create("slot_click", CC_CALLBACK_1(Dice::setTouchableFalse, this));
    auto cardListener = EventListenerCustom::create("use_card", CC_CALLBACK_1(Dice::skipTurn, this));

    // add listeners to event dispactcher
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeEndListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeStatusListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(slotListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(cardListener, this);
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
		sprite->sign = Sprite::create("plane_blue.png");
		sprite->sign->setPosition(Vec2(44, -50));
		sprite->sign->setScale(0.1);
		sprite->addChild(sprite->sign);
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

    // there first number is not random, so the function is called twice
    int roll_num = randomInteger(1, 6);
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
			sign->setTexture("plane_blue.png");
			break;
		case 1: // case green
			eventClick = EventCustom("roll_click_green");
			sign->setTexture("plane_green.png");
			break;
		case 2: // case red
			eventClick = EventCustom("roll_click_red");
			sign->setTexture("plane_red.png");
			break;
		case 3: // case yellow
			eventClick = EventCustom("roll_click_yellow");
			sign->setTexture("plane_yellow.png");
			break;
		}
        eventClick.setUserData((void*)true);
        _eventDispatcher->dispatchEvent(&eventClick);

        // pass roll point to the card generator and ALL planes
        // tell the card slots the dice is clicked
        EventCustom eventRollPT = EventCustom("roll_point");
        eventRollPT.setUserData((void*)&roll_num);
        _eventDispatcher->dispatchEvent(&eventRollPT);

        // pass round to the card generator
        // ask the planes for there position status
        EventCustom eventRoundG = EventCustom("event_round_to_generator_and_planes");
        eventRoundG.setUserData((void*)&round);
        _eventDispatcher->dispatchEvent(&eventRoundG);

        // if roll_num is not 6, the next player rolls the dice
        if (roll_num != 6) {
            round = (round + 1) % 4;

            // skip if the player is nobody
            while (!playerArray[round]) {
                round = (round + 1) % 4;
            }

            // pass round to the card slots
            if (!(statusArray[0] || statusArray[1] || statusArray[2] || statusArray[3])) {
                EventCustom eventRoundS = EventCustom("event_round_to_slots");
                eventRoundS.setUserData((void*)&round);
                _eventDispatcher->dispatchEvent(&eventRoundS);
            }

            // tell the planes if the round changes
            EventCustom eventRoundChange = EventCustom("round_change");
            _eventDispatcher->dispatchEvent(&eventRoundChange);
        }
        return true;
    }
    return false;
}

// callback function to set the touchability of the dice
void Dice::setTouchable(EventCustom* event) {
    can_touch = (bool*)event->getUserData();

    // pass round to the card slots
    EventCustom eventRoundS = EventCustom("event_round_to_slots");
    eventRoundS.setUserData((void*)&round);
    _eventDispatcher->dispatchEvent(&eventRoundS);
}

// callback function to set the touchability to false
void Dice::setTouchableFalse(EventCustom* event) {
    can_touch = false;
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

// callback function to skip a player if the card generator is clicked
void Dice::skipTurn(EventCustom* event) {
    round = (round + 1) % 4;

    // skip if the player is nobody
    while (!playerArray[round]) {
        round = (round + 1) % 4;
    }

    // reset the touchablity of dice
    can_touch = true;

    // pass round to the card slots
    EventCustom eventRoundS = EventCustom("event_round_to_slots");
    eventRoundS.setUserData((void*)&round);
    _eventDispatcher->dispatchEvent(&eventRoundS);

    // tell the planes if the round changes
    EventCustom eventRoundChange = EventCustom("round_change");
    _eventDispatcher->dispatchEvent(&eventRoundChange);
}
