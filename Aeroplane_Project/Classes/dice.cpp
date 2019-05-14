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
    auto AIslotListener = EventListenerCustom::create("AI_slot_click", CC_CALLBACK_1(Dice::setTouchableFalse, this));
    auto cardListener = EventListenerCustom::create("use_card", CC_CALLBACK_1(Dice::skipTurn, this));
    auto chessboardListener = EventListenerCustom::create("event_chess_pass", CC_CALLBACK_1(Dice::AIPass, this));
    auto AINoMoveListener = EventListenerCustom::create("AI_NoMove", CC_CALLBACK_0(Dice::AINoMove, this));
    auto AIDrawListener = EventListenerCustom::create("AI_Draw", CC_CALLBACK_0(Dice::AIDraw, this));
    auto AIUseCardListener = EventListenerCustom::create("AI_UseCard", CC_CALLBACK_1(Dice::AIUseCard, this));
    auto AIMoveListener = EventListenerCustom::create("AI_Move", CC_CALLBACK_1(Dice::AIMove, this));
    auto resetCardListener = EventListenerCustom::create("AI_reset_card", CC_CALLBACK_0(Dice::AISkipTurn, this));
    
    // add listeners to event dispactcher
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeEndListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeStatusListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(slotListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(AIslotListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(cardListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(chessboardListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(AINoMoveListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(AIDrawListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(AIUseCardListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(AIMoveListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(resetCardListener, this);
    return true;
}

Dice* Dice::create(int player0, int player1, int player2, int player3) {
    Dice* sprite = new Dice();
    if (sprite->init()) {
        sprite->autorelease();
        sprite->roll_num = 0;
        sprite->round = 0;
        sprite->can_touch = true;
        sprite->updated_num = 0;
        sprite->playerArray[0] = player0;
        sprite->playerArray[1] = player1;
        sprite->playerArray[2] = player2;
        sprite->playerArray[3] = player3;

        for (int i = 0; i <= 3; ++i) {
            if (sprite->playerArray[i]) {
                sprite->playerCount++;
            }
        }
        
        sprite->sign = Sprite::create();
        sprite->sign->setPosition(Vec2(44, -50));
        sprite->sign->setScale(0.1);
        sprite->sign2 = Sprite::create();
        sprite->sign2->setPosition(Vec2(44, -100));
        sprite->sign2->setScale(0.1);
        sprite->addChild(sprite->sign);
        sprite->addChild(sprite->sign2);
        
        Animation* animation = Animation::create();
        for(int i = 1; i <= 6; ++i) {
            char str[15];
            sprintf(str, "dice%d.png", i);
            animation->addSpriteFrameWithFile(str);
        }
        animation->setRestoreOriginalFrame(true);
        animation->setDelayPerUnit(0.001/1);
        animation->setLoops(30);
        AnimationCache::getInstance()->addAnimation(animation,"Dice");
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
    auto sprite = Sprite::create();
    sprite->setPosition(Vec2(45.7, 45.7));
    this->addChild(sprite);
    Animation* animation = AnimationCache::getInstance()->getAnimation("Dice");
    Animate* animate = Animate::create(animation);
    auto removeself = RemoveSelf::create();
    auto seq = Sequence::create(animate, removeself, NULL);
    sprite->runAction(seq);
    // there first number is not random, so the function is called twice
    int roll_num = randomInteger(1, 6);
    roll_num = randomInteger(1, 6);
    /*roll_num = 6;*/ // only for test, let the roll point be a fixed number
    char str[15];
    sprintf(str, "dice%d.png", roll_num);
    this->setTexture(str);
    return roll_num;
}

bool Dice::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 ptClick = touch->getLocation();
    if (this->getBoundingBox().containsPoint(ptClick) && can_touch) {
        // skip if the player is nobody
        while (!playerArray[round]) {
            round = (round + 1) % 4;
        }
        
        if (playerArray[round] == 1){
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
            log("rpt %d %d", round, roll_num);
            // pass round to the card generator
            // ask the planes for there position status
            EventCustom eventRoundG = EventCustom("event_round_to_generator_and_planes");
            eventRoundG.setUserData((void*)&round);
            _eventDispatcher->dispatchEvent(&eventRoundG);
            log("passround %d", round);
            // if roll_num is not 6, the next player rolls the dice
            if (roll_num != 6) {
                round = (round + 1) % 4;

                // skip if the player is nobody
                while (!playerArray[round]) {
                    round = (round + 1) % 4;
                }
                
                switch (round) {
                    case 0: // case blue
                        sign2->setTexture("plane_blue.png");
                        break;
                    case 1: // case green
                        sign2->setTexture("plane_green.png");
                        break;
                    case 2: // case red
                        sign2->setTexture("plane_red.png");
                        break;
                    case 3: // case yellow
                        sign2->setTexture("plane_yellow.png");
                        break;
                }
                
                // tell the planes if the round changes
                EventCustom eventRoundChange = EventCustom("round_change");
                _eventDispatcher->dispatchEvent(&eventRoundChange);

                if (!(statusArray[0] || statusArray[1] || statusArray[2] || statusArray[3])) {
                    can_touch = true;
                    EventCustom eventRoundS = EventCustom("event_round_to_slots");
                    eventRoundS.setUserData((void*)&round);
                    _eventDispatcher->dispatchEvent(&eventRoundS);
                }
            }
            log("end %d", round);
            statusArray[0] = 0;
            statusArray[1] = 0;
            statusArray[2] = 0;
            statusArray[3] = 0;
            return true;
        }
        else if (playerArray[round] == -1) {
            switch (round) {
                case 0: // case blue
                    sign->setTexture("plane_blue.png");
                    break;
                case 1: // case green
                    sign->setTexture("plane_green.png");
                    break;
                case 2: // case red
                    sign->setTexture("plane_red.png");
                    break;
                case 3: // case yellow
                    sign->setTexture("plane_yellow.png");
                    break;
            }
            AICall();
        }
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
    ++updated_num;
    int* array = (int*)event->getUserData();
    statusArray[*(array + 1)] = *array;

    if (updated_num == 4) {

        // if all the planes of corresponding color are untouchable, skip the color and reset the touchablity of dice
        if (!(statusArray[0] || statusArray[1] || statusArray[2] || statusArray[3])) {
            can_touch = true;
            EventCustom eventRoundS = EventCustom("event_round_to_slots");
            eventRoundS.setUserData((void*)&round);
            _eventDispatcher->dispatchEvent(&eventRoundS);
            log("%d %d %d %d", statusArray[0],statusArray[1],statusArray[2],statusArray[3]);
            log("status done");
        }
        updated_num = 0;
    }
}

// callback function to skip a player if the card generator is clicked
void Dice::skipTurn(EventCustom* event) {
    switch (round) {
    case 0: // case blue
        sign->setTexture("plane_blue.png");
        break;
    case 1: // case green
        sign->setTexture("plane_green.png");
        break;
    case 2: // case red
        sign->setTexture("plane_red.png");
        break;
    case 3: // case yellow
        sign->setTexture("plane_yellow.png");
        break;
    }

    round = (round + 1) % 4;

    // skip if the player is nobody
    while (!playerArray[round]) {
        round = (round + 1) % 4;
    }

    switch (round) {
    case 0: // case blue
        sign2->setTexture("plane_blue.png");
        break;
    case 1: // case green
        sign2->setTexture("plane_green.png");
        break;
    case 2: // case red
        sign2->setTexture("plane_red.png");
        break;
    case 3: // case yellow
        sign2->setTexture("plane_yellow.png");
        break;
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

void Dice::AICall() {
    log("playerArray[round] %d", playerArray[round]);
    log("player %d", round);
    if (playerArray[round] == -1) {
        log("ai");
        can_touch = false;
        EventCustom eventGetCard = EventCustom("event_get_card");
        eventGetCard.setUserData((int*)&round);
        _eventDispatcher->dispatchEvent(&eventGetCard);
        EventCustom eventGetChess = EventCustom("event_get_chess");
        eventGetChess.setUserData((void*)true);
        _eventDispatcher->dispatchEvent(&eventGetChess);
    } else {
        log("human");
    }
}

void Dice::AIPass(EventCustom* event) {
    auto chess = *(CHESS*)event->getUserData();
    chessboard[chess.chessID - 1] = chess;
    ++chessboardStatus;
    if (chessboardStatus == 4 * playerCount) {
        chessboardStatus = 0;

        roll_num = randomInteger(1, 6);
        roll_num = randomInteger(1, 6);
        /*roll_num = 6;*/ // only for test, let the roll point be a fixed number
        EventCustom eventRoundG = EventCustom("event_round_to_generator_and_planes");
        eventRoundG.setUserData((void*)&round);
        _eventDispatcher->dispatchEvent(&eventRoundG);
        EventCustom eventReceiveChessboard = EventCustom("event_receive_chessboard");
        eventReceiveChessboard.setUserData((void*)chessboard);
        _eventDispatcher->dispatchEvent(&eventReceiveChessboard);
        int passArray[2] = {roll_num, round};
        EventCustom eventReceivePoint = EventCustom("event_receive_point");
        eventReceivePoint.setUserData((void*)passArray);
        _eventDispatcher->dispatchEvent(&eventReceivePoint);
        log("AI PASS");
        if (roll_num != 6) {
            round = (round + 1) % 4;
            // skip if the player is nobody
            while (!playerArray[round]) {round = (round + 1) % 4;}
            EventCustom eventRoundS = EventCustom("event_round_to_slots");
            eventRoundS.setUserData((void*)&round);
            _eventDispatcher->dispatchEvent(&eventRoundS);
            // tell the planes if the round changes
            EventCustom eventRoundChange = EventCustom("round_change");
            _eventDispatcher->dispatchEvent(&eventRoundChange);
            switch (round) {
                case 0: // case blue
                    sign2->setTexture("plane_blue.png");
                    break;
                case 1: // case green
                    sign2->setTexture("plane_green.png");
                    break;
                case 2: // case red
                    sign2->setTexture("plane_red.png");
                    break;
                case 3: // case yellow
                    sign2->setTexture("plane_yellow.png");
                    break;
            }
        }
    }
}

void Dice::AINoMove() {
    AIDiceAnimation();
    can_touch = true;
}   

void Dice::AIDraw() {
    AIDiceAnimation();
    EventCustom eventAIDraw2Generator = EventCustom("AI_Draw_2_Generator");
    _eventDispatcher->dispatchEvent(&eventAIDraw2Generator);
}

void Dice::AIUseCard(EventCustom* event) {
    int chessID = *(int*)event->getUserData();
    log("chessID %d", chessID);
    int color = ((chessID - 1) / 4 + 2) % 4;
    int id = (chessID - 1) % 4;
    int ColorIDArray[3] = {color, id, round};
    EventCustom eventAIMove2Slot = EventCustom("AI_UseCard_2_Slot");
    eventAIMove2Slot.setUserData((int*)ColorIDArray);
    _eventDispatcher->dispatchEvent(&eventAIMove2Slot);
    can_touch = true;
}

void Dice::AIMove(EventCustom* event) {
    AIDiceAnimation();
    int chessID = *(int*)event->getUserData();
    int color = ((chessID - 1) / 4 + 2) % 4;
    int id = (chessID - 1) % 4;
    int ColorIDArray[3] = {color, id, roll_num};
    EventCustom eventAIMove2Plane = EventCustom("AI_Move_2_Plane");
    eventAIMove2Plane.setUserData((int*)ColorIDArray);
    _eventDispatcher->dispatchEvent(&eventAIMove2Plane);
}

void Dice::AIDiceAnimation() {
    auto sprite = Sprite::create();
    sprite->setPosition(Vec2(45.7, 45.7));
    this->addChild(sprite);
    Animation* animation = AnimationCache::getInstance()->getAnimation("Dice");
    Animate* animate = Animate::create(animation);
    auto removeself = RemoveSelf::create();
    auto seq = Sequence::create(animate, removeself, NULL);
    sprite->runAction(seq);
    char str[15];
    sprintf(str, "dice%d.png", roll_num);
    this->setTexture(str);
}

void Dice::AISkipTurn() {
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
