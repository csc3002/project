//
//  win_judge.cpp
//  Aeroplane_Project
//
//  Created by Re-Entry on 2019/5/5.
//

#include "win_judge.h"
#include "End_Scene.h"
USING_NS_CC;

// initiate the card generator
bool Win_Judge::init() {
    if (!Sprite::initWithFile("dice.png")) {
        return false;
    }
    setPosition(Vec2(-100, -100));
    setScale(0, 0);

    // set custom event listeners
    auto finishStatusListener = EventListenerCustom::create("finish_status", CC_CALLBACK_1(Win_Judge::setFinishStatusArray, this));

    // add listeners to event dispactcher
    _eventDispatcher->addEventListenerWithSceneGraphPriority(finishStatusListener, this);
    return true;
}

Win_Judge* Win_Judge::create() {
    Win_Judge* sprite = new Win_Judge();
    if (sprite->init()) {
        sprite->autorelease();
    }
    else {
        delete sprite;
        sprite = NULL;
        return NULL;
    }
    return sprite;
}

// callback function to set the status array of corresponding color and check if the player wins
void Win_Judge::setFinishStatusArray(EventCustom* event) {
    int* array = (int*)event->getUserData();
    finishStatusArray[*(array + 1)] = *array;
    if (finishStatusArray[0] && finishStatusArray[1] && finishStatusArray[2] && finishStatusArray[3]) {
        endGame(*(array + 2));
    }
}

// change the scene if someone wins
void Win_Judge::endGame(int player_win_num) {
    auto scene = EndScene::create();
    scene->winner_color = player_win_num;
    scene->addLabel();
    auto tran = TransitionFade::create(2.0, scene);
    Director::getInstance()->replaceScene(tran);
}
