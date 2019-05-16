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
#include "End_Scene.h"
#include "SimpleAudioEngine.h"
#include "planes.h"
#include "dice.h"
#include "card_generator.h"
#include "card_slot.h"
#include "win_judge.h"
#include "AI_interface.h"
#include "evaluator.h"
#include "movegenerator.h"
#include "card_slot_animation.h"
#include <string>
USING_NS_CC;
using namespace std;

Scene* HelloWorld::createScene() {
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    if ( !Scene::init() )
    {
        return false;
    }
//    log("%d", is_advance_mode);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // set background
    auto bg = Sprite::create("background.png");
    bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    bg->setScaleX(visibleSize.width / bg->getContentSize().width);
    bg->setScaleY(visibleSize.height / bg->getContentSize().height);

    // initiate game mode
    // true = advance mode, false = classical mode
    // this->is_advance_mode = true;

    // initiate players and planes
    // players: 1 = human, -1 = ai, 0 = nobody

	auto label = Label::createWithTTF("Mode: Normal", "fonts/Marker Felt.ttf", 36);
	label->setColor(Color3B(0, 0, 0));
	label->setPosition(Vec2(320, 900));
	this->addChild(label, 1);
	auto label2 = Label::createWithTTF("Mode: Offline", "fonts/Marker Felt.ttf", 36);
	label2->setColor(Color3B(0, 0, 0));
	label2->setPosition(Vec2(640, 900));
	this->addChild(label2, 1);
	this->Ad_Mode = label;
	this->Online_Mode = label2;
	
	this->addChild(bg, 0);
	this->schedule(schedule_selector(HelloWorld::update));
	return true;
}

// executed in Start_Scene.cpp
void HelloWorld::setPlane() {

	// count the number of players
	int number_of_players = 0;
	for (int i = 0; i < 4; ++i) {
		if (players[i]) {
			++number_of_players;
		}
	}

	// initiate dice
	auto dice = Dice::create(players[0], players[1], players[2], players[3]);

    // initiate win judge
    auto win_judge = Win_Judge::create();
	win_judge->is_advance_mode = this->is_advance_mode;
	win_judge->online = this->online;
	for (int i = 0; i < 4; ++i) {
		win_judge->players[i] = this->players[i];
	}
	// coordinates of starting area
	const Vec2 blue_start_pts[5] = {Vec2(215, 145), Vec2(145, 145), Vec2(215, 215), Vec2(145, 215), Vec2(314, 140)};
	const Vec2 green_start_pts[5] = {Vec2(145, 745), Vec2(215, 745), Vec2(145, 815), Vec2(215, 815), Vec2(140, 649)};
	const Vec2 red_start_pts[5] = {Vec2(745, 815), Vec2(745, 745), Vec2(815, 815), Vec2(815, 745), Vec2(645, 825)};
	const Vec2 yellow_start_pts[5] = {Vec2(815, 215), Vec2(745, 215), Vec2(815, 145), Vec2(745, 145), Vec2(820, 315)};

	// positions of special points
	const int enter_pt[4] = {39, 0, 13, 26};
	const int turn_pt[4] = {36, 49, 10, 23};
	const int fly_start[4] = {4, 17, 30, 43};
	const int fly_end[4] = {16, 29, 42, 3};
	const int init_rotation[4] = {270, 0, 90, 180};

	Planes* blue[4];
	Planes* green[4];
	Planes* red[4];
	Planes* yellow[4];

	for (int i = 0; i < 4; ++i) {
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

	// initiate card generator and card slots
	auto card_generator = Card_Generator::create();

    const Vec2 card_slot_pts[4] = {Vec2(50, 50), Vec2(50, 910), Vec2(910, 910), Vec2(910, 50)};

	auto card_slot_blue = Card_Slot::create(0, number_of_players, players[0], card_slot_pts[0]);
	card_slot_blue->setPosition(card_slot_blue->pt);

	auto card_slot_green = Card_Slot::create(1, number_of_players, players[1], card_slot_pts[1]);
	card_slot_green->setPosition(card_slot_green->pt);

	auto card_slot_red = Card_Slot::create(2, number_of_players, players[2], card_slot_pts[2]);
	card_slot_red->setPosition(card_slot_red->pt);

	auto card_slot_yellow = Card_Slot::create(3, number_of_players, players[3], card_slot_pts[3]);
	card_slot_yellow->setPosition(card_slot_yellow->pt);

    auto card_slot_animation = Card_Slot_Animation::create();

	// add child
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
    log("%d", this->is_advance_mode);
	if (this->is_advance_mode) {
		this->addChild(card_generator, 1);
        this->addChild(card_slot_animation, 10);
		if (players[0]) {
			this->addChild(card_slot_blue, 1);
		}
		if (players[1]) {
			this->addChild(card_slot_green, 1);
		}
		if (players[2]) {
			this->addChild(card_slot_red, 1);
		}
		if (players[3]) {
			this->addChild(card_slot_yellow, 1);
		}
	}
    
    moveGenerator *mg = new moveGenerator(6, is_advance_mode);
    evaluator *eval = new evaluator();
    auto AI_player = AI_player::create();
    AI_player->setEvaluator(eval);
    AI_player->setMoveGenerator(mg);
	this->addChild(dice, 1);
    this->addChild(win_judge, 1);
    this->addChild(AI_player, 0);
}

void HelloWorld::update(float dt) {
	if (this->online == true) {
		this->Ad_Mode->setString("Mode : Online");
	}
	else {
		this->Ad_Mode->setString("Mode : Offline");
	}
	if (this->is_advance_mode == true) {
		this->Online_Mode->setString("Mode : Advanced");
	}
	else {
		this->Online_Mode->setString("Mode : Normal");
	}
}

