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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "planes.h"
#include "dice.h"
#include "SimpleAudioEngine.h"
#include <string>
USING_NS_CC;
using namespace CocosDenshion;

class HelloWorld: public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
//    int getrandom(Ref* pSender, Sprite* dice);
//    void dice_anim(Sprite* dice);
    
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
//    void setTouchable(std::string str);
//    void setDiceTouchable(Dice::Dice*, bool _can_touch);
//    void setPlanesTouchable(Planes::Planes*, bool _can_touch);
    CREATE_FUNC(HelloWorld);
private:
    cocos2d::Label* labelTouchInfo;
};

#endif // __HELLOWORLD_SCENE_H__
