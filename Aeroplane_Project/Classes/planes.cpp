//
//  planes.cpp
//  Aeroplane_Project
//
//  Created by HRBattery on 2019/4/16.
//
#include "planes.h"
USING_NS_CC;
bool Planes::init() {
    
    if (!Sprite::initWithFile("plane.png")) {
        return false;
    }
    //‘⁄’‚¿ÔΩ¯––“ª–©æ´¡È¿‡µƒ…Ë÷√
    setScale(0.152f, 0.152f);//…Ë÷√Àı∑≈
    //setRotation(90);//À≥ ±’Î∑ΩœÚ
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Planes::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}
Planes* Planes::create() {
    Planes * sprite = new Planes();
    if (sprite->init()) {
        sprite->autorelease();//”–≥Ã–Úøÿ÷∆spriteµƒ…˙√¸÷‹∆⁄£¨
    }
    else
    {
        delete sprite;
        sprite = NULL;
        return NULL;
    }
    return sprite;
}

bool Planes::onTouchBegan(Touch* touch, Event* event){
    Vec2 ptClick = touch->getLocation();
    if (this->getBoundingBox().containsPoint(ptClick))
    {
        auto rotateBy1 = RotateBy::create(0.5,45);
        auto moveTo1 = MoveTo::create(0.5, Vec2(100,200));
        this->runAction(rotateBy1);
        this->runAction(moveTo1);
    }
    return true;
}
