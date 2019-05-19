//
//  card_slot.cpp
//  Aeroplane_Project
//
//  Created by Re-Entry on 2019/4/28.
//

#include "card_slot.h"
USING_NS_CC;

// initiate the card slot
bool Card_Slot::init() {
    if (!Sprite::initWithFile("none.png")) {
        return false;
    }

    // set touch listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Card_Slot::onTouchBegan, this);
    touchListener->setSwallowTouches(true);

    // set custom event listeners
    auto generatorClickListener = EventListenerCustom::create("generator_click", CC_CALLBACK_1(Card_Slot::setCard, this));
    auto roundListener = EventListenerCustom::create("event_round_to_slots", CC_CALLBACK_1(Card_Slot::setTouchable, this));
    auto rollPTListener = EventListenerCustom::create("roll_point", CC_CALLBACK_1(Card_Slot::setTouchableFalse, this));
    auto getCardListener = EventListenerCustom::create("event_get_card", CC_CALLBACK_1(Card_Slot::passCard, this));
    auto AIUseCardListener = EventListenerCustom::create("AI_UseCard_2_Slot", CC_CALLBACK_1(Card_Slot::AIUseCard, this));

    // add listeners to event dispactcher
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(generatorClickListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(roundListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(rollPTListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(getCardListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(AIUseCardListener, this);
    return true;
}

Card_Slot* Card_Slot::create(int _color, int _player_count, int _player_type, Vec2 _pt) {
    Card_Slot* sprite = new Card_Slot();
    if (sprite->init()) {
        sprite->autorelease();
        sprite->color = _color;
        sprite->player_type = _player_type;
        sprite->card_num = 0;
        sprite->player_count = _player_count;
        sprite->can_touch = false;
        sprite->pt = _pt;
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
    if (this->getBoundingBox().containsPoint(ptClick) && can_touch && player_type == 1 && card_num) {

        // set the number of effective rounds
        int round_num = 0;
        if (card_num == 2) {
            round_num = player_count * 5 + 1;
        }
        if (card_num == 3) {
            round_num = player_count * 4 + 1;
        }

        // set the scope of target
        int can_target_be_opponent = 1;
        if (card_num == 1) {
            can_target_be_opponent = 0;
        }

        // pass the card number and effective rounds to ALL planes
        EventCustom eventClick = EventCustom("slot_click");
        int cardInfoArray[4] = {card_num, round_num, can_target_be_opponent, color};
        eventClick.setUserData((int*)cardInfoArray);
        _eventDispatcher->dispatchEvent(&eventClick);

        // the card will be consumed after a click
        card_num = 0;
        this->setTexture("none.png");
        return true;
    }
    return false;
}

// callback function to set the index and the picture of the card
void Card_Slot::setCard(EventCustom* event) {
    int* card_num_round = (int*)event->getUserData();
    if (card_num_round[1] == color) {
        EventCustom animationCall = EventCustom("animation_call");
        animationCall.setUserData((int*)&color);
        _eventDispatcher->dispatchEvent(&animationCall);

        card_num = card_num_round[0];
        if (card_num == 1) {
            this->setTexture("machinegun.png");
        }
        else if (card_num == 2) {
            this->setTexture("protection.png");
        }
        else if (card_num == 3) {
            this->setTexture("stopaction.png");
        }
        else if (card_num == 4) {
            this->setTexture("neutralize.png");
        }
    }
}

// callback function to set the touchability of the card generator
void Card_Slot::setTouchable(EventCustom* event) {
    int round = *(int*)event->getUserData();
    if (round == color) {
        can_touch = true;
    }
    else {
        can_touch = false;
    }
}

// callback function to set the touchability to false
void Card_Slot::setTouchableFalse(EventCustom* event) {
    can_touch = false;
}

void Card_Slot::passCard(EventCustom* event) {
    int round = *(int*)event->getUserData();
    if (round == color) {
        EventCustom eventReceiveCard = EventCustom("event_receive_card");
        eventReceiveCard.setUserData((int*)&card_num);
        _eventDispatcher->dispatchEvent(&eventReceiveCard);
    }
}

void Card_Slot::AIUseCard(EventCustom* event) {
    int* array = (int*)event->getUserData();
    int id = array[1];
    if (color == array[2]){
        int round_num = 0;
        if (card_num == 2) {
            round_num = player_count * 5 + 1;
        }
        if (card_num == 3) {
            round_num = player_count * 4 + 1;
        }
        
        // set the scope of target
        int can_target_be_opponent = 1;
        if (card_num == 1) {
            can_target_be_opponent = 0;
        }
        // pass the card number and effective rounds to ALL planes
        EventCustom eventClick = EventCustom("AI_slot_click");
        int cardInfoArray[5] = {card_num, round_num, can_target_be_opponent, array[0], id};
        eventClick.setUserData((int*)cardInfoArray);
        _eventDispatcher->dispatchEvent(&eventClick);
        
        // the card will be consumed after a click
        card_num = 0;
        this->setTexture("none.png");
    }
}
