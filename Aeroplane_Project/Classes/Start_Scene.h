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

#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class BeginScene: public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	bool online;
	bool advance_mode;
	int num_player;
	int player[4];
	int character[4];
	cocos2d::MenuItemImage* option1; // start game option
	cocos2d::MenuItemImage* option2; // help option
	cocos2d::MenuItemImage* option3; // exit option
	cocos2d::MenuItemImage* option_back; // back option in the menu
	cocos2d::MenuItemImage* option_online; // online option
	cocos2d::MenuItemImage* option_offline; // exit option
	cocos2d::MenuItemImage* option_normal; // normal option
	cocos2d::MenuItemImage* option_advanced; // advanced option
	cocos2d::Sprite* choose_bg; // choose_background
	cocos2d::Sprite* problem_bg; // problem_background
	cocos2d::MenuItemImage* exit; // exit the problem
	cocos2d::MenuItemImage* option_AI_1; // choose one AI
	cocos2d::MenuItemImage* option_AI_2; // choose two AI
	cocos2d::MenuItemImage* option_AI_3; // choose three AI
	cocos2d::MenuItemImage* option_AI_4; // choose four AI
	cocos2d::MenuItemImage* option_player_one; // choose one player
	cocos2d::MenuItemImage* option_player_two; // choose two player
	cocos2d::MenuItemImage* option_player_three; // choose three player
	cocos2d::MenuItemImage* option_player_four; // choose four player
	cocos2d::MenuItemImage* cancel_1;  //cancel button
	cocos2d::MenuItemImage* cancel_2;
	cocos2d::MenuItemImage* cancel_3;
	cocos2d::MenuItemImage* cancel_4;
	cocos2d::MenuItemImage* gamestart;
	cocos2d::MenuItemImage* option_reset;
	cocos2d::Label* player1;
	cocos2d::Label* player2;
	cocos2d::Label* player3;
	cocos2d::Label* player4;
	cocos2d::Label* test;
	cocos2d::Sprite* plane1;
	cocos2d::Sprite* plane2;
	cocos2d::Sprite* plane3;
	cocos2d::Sprite* plane4;
	
	void BeginScene::addplayer(Ref* pSender, int index);
	void BeginScene::addcomputer(Ref* pSender, int index);
	void BeginScene::delplayer(Ref* pSender, int index);
	void BeginScene::change_char(Ref* pSender, int index, int num);
	void BeginScene::update(float dt);
	void BeginScene::reset(Ref* pSender);
	void BeginScene::player_show();
	void Problem_show(Ref* pSender);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void refresh1(cocos2d::Ref* pSender);
	void refresh_menu(cocos2d::Ref* pSender);
	void refresh2(cocos2d::Ref* pSender);
	void refresh3(cocos2d::Ref* pSender, bool mode);
	void BeginScene::refresh2_1(Ref* pSender); // mode = true -> advanced, mode = false -> normal
	void startGame(cocos2d::Ref* pSender, Scene* start_scene, bool online);
    
    // implement the "static create()" method manually
    CREATE_FUNC(BeginScene);
};

#endif // __START_SCENE_H__
