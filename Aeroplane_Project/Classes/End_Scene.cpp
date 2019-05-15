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

 //
 //  End_Scene.cpp
 //  Aeroplane_Project
 //
 //  Created by Re-Entry on 2019/5/5.
 //

#include "End_Scene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* EndScene::createScene() {
    return EndScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool EndScene::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // set background
    auto bg = Sprite::create("Start.png");
    bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    bg->setScaleX(visibleSize.width / bg->getContentSize().width);
    bg->setScaleY(visibleSize.height / bg->getContentSize().height);
    this->addChild(bg, 0);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(EndScene::menuCloseCallback, this));

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

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    auto exitItem = MenuItemImage::create(
        "start3.png",
        "start3.png",
        CC_CALLBACK_1(EndScene::menuCloseCallback, this));

    if (exitItem == nullptr ||
        exitItem->getContentSize().width <= 0 ||
        exitItem->getContentSize().height <= 0)
    {
        problemLoading("'start3.png' and 'start3.png'");
    }
    else
    {
        float x = visibleSize.width / 2;
        float y = visibleSize.height / 4;
        exitItem->setPosition(Vec2(x, y));
        exitItem->setScale(2);
    }

    // create exit menu, it's an autorelease object
    auto exit = Menu::create(exitItem, NULL);
    exit->setPosition(Vec2::ZERO);
    this->addChild(exit, 1);

    return true;
}

void EndScene::menuCloseCallback(Ref* pSender) {
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

// show who wins
void EndScene::addLabel() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label_blue_win = Label::createWithTTF("Blue wins!", "fonts/Marker Felt.ttf", 150);
    label_blue_win->setTextColor(Color4B(0, 0, 0, 255));
    if (label_blue_win == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        float x = visibleSize.width / 2;
        float y = visibleSize.height / 2;
        label_blue_win->setPosition(Vec2(x, y));

        if (winner_color == 0) {
            // add the label as a child to this layer
            this->addChild(label_blue_win, 1);
        }
    }

    auto label_green_win = Label::createWithTTF("Green wins!", "fonts/Marker Felt.ttf", 150);
    label_green_win->setTextColor(Color4B(0, 0, 0, 255));
    if (label_green_win == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        float x = visibleSize.width / 2;
        float y = visibleSize.height / 2;
        label_green_win->setPosition(Vec2(x, y));

        if (winner_color == 1) {
            // add the label as a child to this layer
            this->addChild(label_green_win, 1);
        }
    }

    auto label_red_win = Label::createWithTTF("Red wins!", "fonts/Marker Felt.ttf", 150);
    label_red_win->setTextColor(Color4B(0, 0, 0, 255));
    if (label_red_win == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        float x = visibleSize.width / 2;
        float y = visibleSize.height / 2;
        label_red_win->setPosition(Vec2(x, y));

        if (winner_color == 2) {
            // add the label as a child to this layer
            this->addChild(label_red_win, 1);
        }
    }

    auto label_yellow_win = Label::createWithTTF("Yellow wins!", "fonts/Marker Felt.ttf", 150);
    label_yellow_win->setTextColor(Color4B(0, 0, 0, 255));
    if (label_yellow_win == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        float x = visibleSize.width / 2;
        float y = visibleSize.height / 2;
        label_yellow_win->setPosition(Vec2(x, y));

        if (winner_color == 3) {
            // add the label as a child to this layer
            this->addChild(label_yellow_win, 1);
        }
    }
}
