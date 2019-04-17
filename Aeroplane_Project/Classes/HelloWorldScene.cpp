/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "planes.h"

USING_NS_CC;

//}

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	labelTouchInfo = Label::createWithSystemFont("Touch or clicksomewhere to begin", "Arial", 80);
    labelTouchInfo->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
                                     Director::getInstance()->getVisibleSize().height / 2));
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    this->addChild(labelTouchInfo,1);
    auto visibleSize = Director::getInstance()->getVisibleSize();
	log("[%f, %f]", visibleSize.width, visibleSize.height);

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// floor Sprite
	//auto  floor = Sprite::create("white.jpg");
	//floor->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	//floor->setScaleX(visibleSize.width / floor->getContentSize().width);
	//floor->setScaleY(visibleSize.height / floor->getContentSize().height);
	//this->addChild(floor, 0);
	//background Sprite
	auto  bg = Sprite::create("background.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bg->setScaleX(visibleSize.width / bg->getContentSize().width);
	bg->setScaleY(visibleSize.height / bg->getContentSize().height);
	this->addChild(bg, 0);
	auto s = Planes::create();
	s->setPosition(Vec2(630, 737));//设置精灵的位置
	s->setRotation(90);
	this->addChild(s,0);
	
	/*auto  plane = Sprite::create("plane.png");
	plane->setPosition(Vec2(480, 775));
	plane->setScaleX(50 / plane->getContentSize().width);
	plane->setScaleY(50 / plane->getContentSize().height);
	this->addChild(plane, 0);*/
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::runPlane, this,s));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }
	auto control1 = MenuItemImage::create(
		"button1.png",
		"button1_choosen.png",
		CC_CALLBACK_1(HelloWorld::runPlane, this, s));
	float x = 900;
	float y = 480;
	control1->setPosition(Vec2(x, y));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,control1, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    //if (label == nullptr)
    //{
    //    problemLoading("'fonts/Marker Felt.ttf'");
    //}
    //else
    //{
    //    // position the label on the center of the screen
    //    label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                            origin.y + visibleSize.height - label->getContentSize().height));

    //    // add the label as a child to this layer
    //    this->addChild(label, 1);
    //}

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    //if (sprite == nullptr)
    //{
    //    problemLoading("'HelloWorld.png'");
    //}
    //else
    //{
    //    // position the sprite on the center of the screen
    //    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //}
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
//void HelloWorld::runPlane(Ref* pSender, Sprite* p1)
//{
//	//Close the cocos2d-x game scene and quit the application
//	CCActionInterval* rotateBy1 = CCRotateBy::create(0.5, 45);
//	CCMoveTo* moveTo1 = CCMoveTo::create(0.5, ccp(p1->getPositionX() + 37, p1->getPositionY()-17));
//	p1->runAction(rotateBy1);
//	p1->runAction(moveTo1);
//
//	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
//
//	//EventCustom customEndEvent("game_scene_close_event");
//	//_eventDispatcher->dispatchEvent(&customEndEvent);
//
//
//}
void HelloWorld::runPlane(Ref* pSender, Sprite* p1)
{
	//Close the cocos2d-x game scene and quit the application
	ActionInterval* rotateBy1 = RotateBy::create(0.5,45);
	MoveTo* moveTo1 = MoveTo::create(0.5, Vec2(p1->getPositionX()-16, p1->getPositionY()-40));
	p1->runAction(rotateBy1);
	p1->runAction(moveTo1);

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    labelTouchInfo->setPosition(touch->getLocation());
    labelTouchInfo->setString("You Touched Here");
    return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    cocos2d::log("touch ended");
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    cocos2d::log("touch moved");
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
    cocos2d::log("touch cancelled");
}
