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
#include <string>
USING_NS_CC;
using namespace std;

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
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // add touchlistener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    // touch info, for test
	labelTouchInfo = Label::createWithSystemFont("Touch or clicksomewhere to begin", "Arial", 18);
    labelTouchInfo->setTextColor(Color4B(0,0,0,255));
    labelTouchInfo->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
                                     Director::getInstance()->getVisibleSize().height / 2));
    
    // set background
	auto  bg = Sprite::create("background.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bg->setScaleX(visibleSize.width / bg->getContentSize().width);
	bg->setScaleY(visibleSize.height / bg->getContentSize().height);
    
    // initial players and planes
	// players: 1 = human, -1 = ai, 0 = nobody

	int players[4] = {1, 1, 1, 1};
    const Vec2 blue_start_pts[5] = {Vec2(215, 145), Vec2(145, 145), Vec2(215, 215), Vec2(145, 215), Vec2(314, 140)};
    const Vec2 green_start_pts[5] = {Vec2(145, 745), Vec2(215, 745), Vec2(145, 815), Vec2(215, 815), Vec2(140, 649)};
    const Vec2 red_start_pts[5] = {Vec2(745, 815), Vec2(745, 745), Vec2(815, 815), Vec2(815, 745), Vec2(645, 825)};
    const Vec2 yellow_start_pts[5] = {Vec2(815, 215), Vec2(745, 215), Vec2(815, 145), Vec2(745, 145), Vec2(820, 315)};
    
    const int enter_pt[4] = {39, 0, 13, 26};
    const int turn_pt[4] = {36, 49, 10, 23};
    const int fly_start[4] = {4, 17, 30, 43};
    const int fly_end[4] = {16, 29, 42, 3};
    const int init_rotation[4] ={0, 90, 180, 270};

    // color, id, enter_pt, turn_pt, fly_start, fly_end, init_rotation, start_pt, take_off_pt, icon, status = "ground", position = -1, roll
    Planes* blue[4];
    Planes* green[4];
    Planes* red[4];
    Planes* yellow[4];
    
    for (int i = 0; i < 4; ++i){
        blue[i] = Planes::create(0, i, enter_pt[0], turn_pt[0], fly_start[0], fly_end[0], init_rotation[0], blue_start_pts[i], blue_start_pts[4], "plane_blue.png");
        blue[i]->setPosition(blue[i]->start_pt);
        green[i] = Planes::create(1, i, enter_pt[1], turn_pt[1], fly_start[1], fly_end[1], init_rotation[1], green_start_pts[i], green_start_pts[4], "plane_green.png");
        green[i]->setPosition(green[i]->start_pt);
        red[i] = Planes::create(2, i, enter_pt[2], turn_pt[2], fly_start[2], fly_end[2], init_rotation[2], red_start_pts[i], red_start_pts[4], "plane_red.png");
        red[i]->setPosition(red[i]->start_pt);
        yellow[i] = Planes::create(3, i, enter_pt[3], turn_pt[3], fly_start[3], fly_end[3], init_rotation[3], yellow_start_pts[i], yellow_start_pts[4], "plane_yellow.png");
        yellow[i]->setPosition(yellow[i]->start_pt);
    }
    auto blue_plane_0 = blue[0];
    auto blue_plane_1 = blue[1];
    auto blue_plane_2 = blue[2];
    auto blue_plane_3 = blue[3];
    auto green_plane_0 = green[0];
    auto green_plane_1 = green[1];
    auto green_plane_2 = green[2];
    auto green_plane_3 = green[3];
    auto red_plane_0 = red[0];
    auto red_plane_1 = red[1];
    auto red_plane_2 = red[2];
    auto red_plane_3 = red[3];
    auto yellow_plane_0 = yellow[0];
    auto yellow_plane_1 = yellow[1];
    auto yellow_plane_2 = yellow[2];
    auto yellow_plane_3 = yellow[3];
    
//    auto blue_plane_0 = Planes::create(0, 0, enter_pt[0], turn_pt[0], fly_start[0], fly_end[0], init_rotation[0], blue_start_pts[0], blue_start_pts[4], "plane_blue.png");
//    blue_plane_0->setPosition(blue_plane_0->start_pt);
//
//    auto blue_plane_1 = Planes::create(0, 1, enter_pt[0], turn_pt[0], fly_start[0], fly_end[0], init_rotation[0], blue_start_pts[1], blue_start_pts[4], "plane_blue.png");
//    blue_plane_1->setPosition(blue_plane_1->start_pt);
//
//    auto blue_plane_2 = Planes::create(0, 2, enter_pt[0], turn_pt[0], fly_start[0], fly_end[0], init_rotation[0], blue_start_pts[2], blue_start_pts[4], "plane_blue.png");
//    blue_plane_2->setPosition(blue_plane_2->start_pt);
//
//    auto blue_plane_3 = Planes::create(0, 3, enter_pt[0], turn_pt[0], fly_start[0], fly_end[0], init_rotation[0], blue_start_pts[3], blue_start_pts[4], "plane_blue.png");
//    blue_plane_3->setPosition(blue_plane_3->start_pt);
//
//    auto red_plane_0 = Planes::create(2, 0, enter_pt[2], turn_pt[2], fly_start[2], fly_end[2], init_rotation[2], red_start_pts[0], red_start_pts[4], "plane_red.png");
//    red_plane_0->setPosition(red_plane_0->start_pt);
//
//    auto red_plane_1 = Planes::create(2, 1, enter_pt[2], turn_pt[2], fly_start[2], fly_end[2], init_rotation[2], red_start_pts[1], red_start_pts[4], "plane_red.png");
//    red_plane_1->setPosition(red_plane_1->start_pt);
//
//    auto red_plane_2 = Planes::create(2, 2, enter_pt[2], turn_pt[2], fly_start[2], fly_end[2], init_rotation[2], red_start_pts[2], red_start_pts[4], "plane_red.png");
//    red_plane_2->setPosition(red_plane_2->start_pt);
//
//    auto red_plane_3 = Planes::create(2, 3, enter_pt[2], turn_pt[2], fly_start[2], fly_end[2], init_rotation[2], red_start_pts[3], red_start_pts[4], "plane_red.png");
//    red_plane_3->setPosition(red_plane_3->start_pt);

//    auto test_plane = Planes::create();
//    test_plane->setPosition(Vec2(480, 223));
//    this->addChild(test_plane, 0);

//    auto test_plane_2 = Planes::create(2, 4, 13, 10, 30, 42, 180, Vec2(780, 780), Vec2(645, 825), "plane_red.png", "outer", 24);
//    test_plane_2->setPosition(Vec2(300, 300));
//    test_plane_2->setRotation(270);
//    this->addChild(test_plane_2, 0);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::runPlane, this, red_plane_0));
    
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
    
    if (players[0]) {
        this->addChild(blue_plane_0, 10);
        this->addChild(blue_plane_1, 10);
        this->addChild(blue_plane_2, 10);
        this->addChild(blue_plane_3, 10);
    }
    
    if (players[1]) {
        this->addChild(green_plane_0, 10);
        this->addChild(green_plane_1, 10);
        this->addChild(green_plane_2, 10);
        this->addChild(green_plane_3, 10);
    }
    
	if (players[2]) {
		this->addChild(red_plane_0, 10);
		this->addChild(red_plane_1, 10);
		this->addChild(red_plane_2, 10);
		this->addChild(red_plane_3, 10);
	}
	
    if (players[3]) {
        this->addChild(yellow_plane_0, 10);
        this->addChild(yellow_plane_1, 10);
        this->addChild(yellow_plane_2, 10);
        this->addChild(yellow_plane_3, 10);
    }

    this->addChild(closeItem, 1);
    this->addChild(labelTouchInfo,1);
    this->addChild(bg, 0);
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

void HelloWorld::runPlane(Ref* pSender, Sprite* p1)
{
	//Close the cocos2d-x game scene and quit the application
	ActionInterval* rotateBy1 = RotateBy::create(0.5,45);
	MoveTo* moveTo1 = MoveTo::create(0.5, Vec2(p1->getPositionX()-16, p1->getPositionY()-40));
	p1->runAction(rotateBy1);
	p1->runAction(moveTo1);
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
