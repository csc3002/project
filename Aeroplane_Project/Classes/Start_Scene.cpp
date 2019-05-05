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

#include "Start_Scene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* BeginScene::createScene()
{
    return BeginScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool BeginScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	this->num_player = 0;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto  bg = Sprite::create("Start.png");
	bg->setPosition(ccp(480,480));
	bg->setScaleX((960 / bg->getContentSize().width));
	bg->setScaleY((960 / bg->getContentSize().height));
	this->addChild(bg, 0);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(BeginScene::menuCloseCallback, this));
	auto start_scene = HelloWorld::createScene();
	auto option1 = MenuItemImage::create(
		"start1.png",
		"start1.png",
		CC_CALLBACK_1(BeginScene::refresh2 ,this));
	option1->setPosition(ccp(480,585));
	option1->setScale(2);
	this->option1 = option1;
	auto option2 = MenuItemImage::create(
		"start2.png",
		"start2.png",
		CC_CALLBACK_1(BeginScene::refresh_menu, this));
	option2->setPosition(ccp(480, 480));
	option2->setScale(2);
	this->option2 = option2;
	auto option3 = MenuItemImage::create(
		"start3.png",
		"start3.png",
		CC_CALLBACK_1(BeginScene::menuCloseCallback, this));
	option3->setPosition(ccp(480, 375));
	option3->setScale(2);
	this->option3 = option3;
	auto option_back = MenuItemImage::create(
		"back.png",
		"back.png",
		CC_CALLBACK_1(BeginScene::refresh1, this));
	option_back->setPosition(ccp(150, 100));
	option_back->setScale(0);
	this->option_back = option_back;
	auto option_online = MenuItemImage::create(
		"online_button.png",
		"online_button.png",
		CC_CALLBACK_1(BeginScene::Problem_show,this));
	option_online->setPosition(ccp(480, 540));
	option_online->setScale(0);
	this->option_online = option_online;
	auto option_offline = MenuItemImage::create(
		"offline_button.png",
		"offline_button.png",
		CC_CALLBACK_1(BeginScene::refresh2_1,this));
	option_offline->setPosition(ccp(480, 420));
	option_offline->setScale(0);
	this->option_offline = option_offline;

	auto option_advanced = MenuItemImage::create(
		"advanced_button.png",
		"advanced_button.png",
		CC_CALLBACK_1(BeginScene::refresh3, this ,true));
	option_advanced->setPosition(ccp(480, 540));
	option_advanced->setScale(0);
	this->option_advanced = option_advanced;

	auto option_normal = MenuItemImage::create(
		"normal_button.png",
		"normal_button.png",
		CC_CALLBACK_1(BeginScene::refresh3, this, false));
	option_normal->setPosition(ccp(480, 420));
	option_normal->setScale(0);
	this->option_normal = option_normal;

	auto choose_bg = Sprite::create("choose_bg.png");
	this->addChild(choose_bg, 0);
	this->choose_bg = choose_bg;
	this->choose_bg->setPosition(ccp(480, 480));
	this->choose_bg->setScale(0);

	auto problem_bg = Sprite::create("Problem_bg.png");
	this->addChild(problem_bg, 0);
	this->problem_bg = problem_bg;
	this->problem_bg->setPosition(ccp(480, 520));
	this->problem_bg->setScale(0);

	auto exit = MenuItemImage::create(
		"OK.png",
		"OK.png",
		CC_CALLBACK_1(BeginScene::refresh2, this));
	exit->setPosition(ccp(480, 480));
	exit->setScale(0);
	this->exit = exit;
	
	auto option_reset = MenuItemImage::create(
		"reset.png",
		"reset.png",
		CC_CALLBACK_1(BeginScene::reset, this));
	option_reset->setPosition(ccp(860, 25));
	option_reset->setScale(0);
	this->option_reset = option_reset;

	this->exit = exit;
	this->player1 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 36);
	this->player1->setColor(ccc3(0, 0, 0));
	this->addChild(player1, 0);
	this->player2 = Label::createWithTTF(" ", "fonts/Marker Felt.ttf", 36);
	this->player2->setColor(ccc3(0, 0, 0));
	this->addChild(player2, 0);
	this->player3 = Label::createWithTTF(" ", "fonts/Marker Felt.ttf", 36);
	this->player3->setColor(ccc3(0, 0, 0));
	this->addChild(player3, 0);
	this->player4 = Label::createWithTTF(" ", "fonts/Marker Felt.ttf", 36);
	this->player4->setColor(ccc3(0, 0, 0));
	this->addChild(player4, 0);

	this->test = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 36);
	this->test->setColor(ccc3(0, 0, 0));
	this->test->setPosition(ccp(70,400));
	this->test->setScale(0);
	this->addChild(test, 0);

	this->player1->setPosition(ccp(135, 560));
	this->player2->setPosition(ccp(365, 560));
	this->player3->setPosition(ccp(595, 560));
	this->player4->setPosition(ccp(825, 560));
	this->player1->setScale(0);
	this->player2->setScale(0);
	this->player3->setScale(0);
	this->player4->setScale(0);
	auto option_player_one = MenuItemImage::create(
		"Add_Player.png",
		"Add_Player.png",
		CC_CALLBACK_1(BeginScene::addplayer, this , 1));
	option_player_one->setPosition(ccp(135, 135));
	option_player_one->setScale(0);
	this->option_player_one = option_player_one;


	auto option_AI_1 = MenuItemImage::create(
		"Add_Computer.png",
		"Add_Computer.png",
		CC_CALLBACK_1(BeginScene::addcomputer, this, 1));
	option_AI_1->setPosition(ccp(135, 80));
	option_AI_1->setScale(0);
	this->option_AI_1 = option_AI_1;
	auto option_player_two = MenuItemImage::create(
		"Add_Player.png",
		"Add_Player.png",
		CC_CALLBACK_1(BeginScene::addplayer, this, 2));
	option_player_two->setPosition(ccp(365, 135));
	option_player_two->setScale(0);
	this->option_player_two = option_player_two;
	auto option_AI_2 = MenuItemImage::create(
		"Add_Computer.png",
		"Add_Computer.png",
		CC_CALLBACK_1(BeginScene::addcomputer, this, 2));
	option_AI_2->setPosition(ccp(365, 80));
	option_AI_2->setScale(0);
	this->option_AI_2 = option_AI_2;
	auto option_player_three = MenuItemImage::create(
		"Add_Player.png",
		"Add_Player.png",
		CC_CALLBACK_1(BeginScene::addplayer, this, 3));
	option_player_three->setPosition(ccp(595, 135));
	option_player_three->setScale(0);
	this->option_player_three = option_player_three;
	auto option_AI_3 = MenuItemImage::create(
		"Add_Computer.png",
		"Add_Computer.png",
		CC_CALLBACK_1(BeginScene::addcomputer, this, 3));
	option_AI_3->setPosition(ccp(595, 80));
	option_AI_3->setScale(0);
	this->option_AI_3 = option_AI_3;
	auto option_player_four = MenuItemImage::create(
		"Add_Player.png",
		"Add_Player.png",
		CC_CALLBACK_1(BeginScene::addplayer, this, 4));
	option_player_four->setPosition(ccp(825, 135));
	option_player_four->setScale(0);
	this->option_player_four = option_player_four;
	auto option_AI_4 = MenuItemImage::create(
		"Add_Computer.png",
		"Add_Computer.png",
		CC_CALLBACK_1(BeginScene::addcomputer, this, 4));
	option_AI_4->setPosition(ccp(825, 80));
	option_AI_4->setScale(0);
	this->option_AI_4 = option_AI_4;
	auto option_gamestart = MenuItemImage::create(
		"start1.png",
		"start1.png",
		CC_CALLBACK_1(BeginScene::startGame, this, start_scene, false));
	this->gamestart = option_gamestart;
	this->gamestart->setScale(0);
	this->gamestart->setPosition(ccp(480,25));

	auto cancel_1 = MenuItemImage::create(
		"cancel.png",
		"cancel.png",
		CC_CALLBACK_1(BeginScene::delplayer, this, 1));
	cancel_1->setPosition(ccp(215, 520));
	cancel_1->setScale(0);
	this->cancel_1 = cancel_1;

	auto cancel_2 = MenuItemImage::create(
		"cancel.png",
		"cancel.png",
		CC_CALLBACK_1(BeginScene::delplayer, this, 2));
	cancel_2->setPosition(ccp(445, 520));
	cancel_2->setScale(0);
	this->cancel_2 = cancel_2;

	auto cancel_3 = MenuItemImage::create(
		"cancel.png",
		"cancel.png",
		CC_CALLBACK_1(BeginScene::delplayer, this, 3));
	cancel_3->setPosition(ccp(675, 520));
	cancel_3->setScale(0);
	this->cancel_3 = cancel_3;

	auto cancel_4 = MenuItemImage::create(
		"cancel.png",
		"cancel.png",
		CC_CALLBACK_1(BeginScene::delplayer, this, 4));
	cancel_4->setPosition(ccp(905, 520));
	cancel_4->setScale(0);
	this->cancel_4 = cancel_4;

	auto plane1 = Sprite::create();
	this->plane1 = plane1;
	this->plane1->setPosition(ccp(135,335));
	this->plane1->setScale(0);
	this->addChild(plane1, 1);

	auto plane2 = Sprite::create();
	this->plane2 = plane2;
	this->plane2->setPosition(ccp(365, 335));
	this->plane2->setScale(0);
	this->addChild(plane2, 1);

	auto plane3 = Sprite::create();
	this->plane3 = plane3;
	this->plane3->setPosition(ccp(595, 335));
	this->plane3->setScale(0);
	this->addChild(plane3, 1);

	auto plane4 = Sprite::create();
	this->plane4 = plane4;
	this->plane4->setPosition(ccp(825, 335));
	this->plane4->setScale(0);
	this->addChild(plane4, 1);
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
	auto menu = Menu::create(option1, option2, option3, option_back, option_online, option_offline, option_advanced, option_normal, closeItem, option_player_one, option_AI_1, option_player_two, option_AI_2
		, option_player_three, option_AI_3, option_player_four, option_AI_4, option_gamestart, exit, option_reset, cancel_1, cancel_2, cancel_3, cancel_4,
		NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	this->schedule(schedule_selector(BeginScene::update));
    return true;
}


void BeginScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
void BeginScene::reset(Ref* pSender) {
	for (int i = 0; i < 4;i++) {
		this->player[i] = 0;
		this->character[i] = 0;
	}
	this->num_player = 0;
}
void BeginScene::update(float dt)
{	
	if (this->num_player >= 2) {
		this->gamestart->setScale(1.5);
	}
	else {
		this->gamestart->setScale(0);
	}
	this->player_show();
}
void BeginScene::player_show() {
	if (this->player[0] == 1) {
		this->player1->setString("Player 1");
		this->plane1->setTexture("plane_blue.png");
		this->plane1->setRotation(270);
		this->plane1->setScale(0.32);
		this->cancel_1->setScale(0.7);
		this->test->setString("1");
	}
	else if (this->player[0] == -1) {
		this->player1->setString("Computer 1");
		this->plane1->setTexture("plane_blue.png");
		this->plane1->setRotation(270);
		this->plane1->setScale(0.32);
		this->cancel_1->setScale(0.7);
		this->test->setString("1");
	}
	else {
		this->player1->setString(" ");
		this->cancel_1->setScale(0);
		this->plane1->setScale(0);
	}
	if (this->player[1] == 1) {
		this->player2->setString("Player 2");
		this->plane2->setTexture("plane_green.png");
		this->plane2->setRotation(270);
		this->cancel_2->setScale(0.7);
		this->plane2->setScale(0.32);
	}
	else if (this->player[1] == -1) {
		this->player2->setString("Computer 2");
		this->plane2->setTexture("plane_green.png");
		this->plane2->setRotation(270);
		this->cancel_2->setScale(0.7);
		this->plane2->setScale(0.32);
	}
	else {
		this->player2->setString(" ");
		this->cancel_2->setScale(0);
		this->plane2->setScale(0);
	}
	if (this->player[2] == 1) {
		this->player3->setString("Player 3");
		this->plane3->setTexture("plane_red.png");
		this->plane3->setRotation(270);
		this->cancel_3->setScale(0.7);
		this->plane3->setScale(0.32);
	}
	else if (this->player[2] == -1) {
		this->player3->setString("Computer 3");
		this->plane3->setTexture("plane_red.png");
		this->plane3->setRotation(270);
		this->cancel_3->setScale(0.7);
		this->plane3->setScale(0.32);
	}
	else {
		this->player3->setString(" ");
		this->cancel_3->setScale(0);
		this->plane3->setScale(0);
	}
	if (this->player[3] == 1) {
		this->player4->setString("Player 4");
		this->plane4->setTexture("plane_yellow.png");
		this->plane4->setRotation(270);
		this->cancel_4->setScale(0.7);
		this->plane4->setScale(0.32);
	}
	else if (this->player[3] == -1) {
		this->player4->setString("Computer 4");
		this->plane4->setTexture("plane_yellow.png");
		this->plane4->setRotation(270);
		this->cancel_4->setScale(0.7);
		this->plane4->setScale(0.32);
	}
	else {
		this->player4->setString(" ");
		this->cancel_4->setScale(0);
		this->plane4->setScale(0);
	}
}

void BeginScene::addplayer(Ref* pSender, int index)
{
	if (this->player[index - 1] == 0) {
		this->num_player += 1;
	}	
	this->player[index - 1] = 1;
	
}
void BeginScene::addcomputer(Ref* pSender, int index)
{
	if (this->player[index - 1] == 0) {
		this->num_player += 1;
	}
	this->player[index - 1] = -1;
}
void BeginScene::delplayer(Ref* pSender, int index)
{
	this->num_player -= 1;
	this->player[index - 1] = 0;
}
void BeginScene::change_char(Ref* pSender, int index, int num)
{
	this->character[index - 1] = num;
}
void BeginScene::refresh1(Ref* pSender)
{
	this->option1->setScale(2);
	this->option2->setScale(2);
	this->option3->setScale(2);
	this->option_back->setScale(0);
	this->option_offline->setScale(0);
	this->option_online->setScale(0);
	this->option_advanced->setScale(0);
	this->option_normal->setScale(0);
	this->choose_bg->setScale(0);
	this->problem_bg->setScale(0);
	this->exit->setScale(0);
	this->player1->setScale(0);
	this->player2->setScale(0);
	this->player3->setScale(0);
	this->player4->setScale(0);
	this->option_player_one->setScale(0);
	this->option_AI_1->setScale(0);
	this->option_player_two->setScale(0);
	this->option_AI_2->setScale(0);
	this->option_player_three->setScale(0);
	this->option_AI_3->setScale(0);
	this->option_player_four->setScale(0);
	this->option_AI_4->setScale(0);
	this->gamestart->setScale(0);
	this->plane1->setScale(0);
	this->plane2->setScale(0);
	this->plane3->setScale(0);
	this->plane4->setScale(0);
	this->test->setScale(0);
	this->option_reset->setScale(0);
	this->reset(this);
	this->advance_mode = false;
	//this->option_two_AI->setScale(0);
	//this->option_three_AI->setScale(0);
	
	//this->option_two_player->setScale(0);
	//this->option_three_player->setScale(0);

}
void BeginScene::refresh2(Ref* pSender)
{
	this->option1->setScale(0);
	this->option2->setScale(0);
	this->option3->setScale(0);
	this->option_back->setScale(1.5);
	this->option_offline->setScale(2);
	this->option_online->setScale(2);
	this->problem_bg->setScale(0);
	this->exit->setScale(0);
	//this->option_one_AI->setScale(0);
	//this->option_two_AI->setScale(0);
	//this->option_three_AI->setScale(0);
	//this->option_one_player->setScale(0);
	//this->option_two_player->setScale(0);
	//this->option_three_player->setScale(0);

}
void BeginScene::Problem_show(Ref* pSender) {
	this->option_back->setScale(0);
	this->option_offline->setScale(0);
	this->option_online->setScale(0);
	this->problem_bg->setScale(2);
	this->exit->setScale(2);
}
void BeginScene::refresh2_1(Ref* pSender ) //I forget to set the mode select
{
	this->option1->setScale(0);
	this->option2->setScale(0);
	this->option3->setScale(0);
	this->option_back->setScale(1.5);
	this->option_offline->setScale(0);
	this->option_online->setScale(0);
	this->option_advanced->setScale(2);
	this->option_normal->setScale(2);
	//this->option_one_AI->setScale(0);
	//this->option_two_AI->setScale(0);
	//this->option_three_AI->setScale(0);
	//this->option_one_player->setScale(0);
	//this->option_two_player->setScale(0);
	//this->option_three_player->setScale(0);

}
void BeginScene::refresh3(Ref* pSender, bool mode)
{
	this->advance_mode = mode;
	this->option1->setScale(0);
	this->option2->setScale(0);
	this->option3->setScale(0);
	this->option_back->setScale(1);
	this->option_back->setPosition(ccp(100,25));
	this->option_reset->setScale(1);
	this->option_offline->setScale(0);
	this->option_online->setScale(0);
	this->option_advanced->setScale(0);
	this->option_normal->setScale(0);
	this->choose_bg->setScale(1.5);
	this->player1->setScale(1);
	this->player2->setScale(1);
	this->player3->setScale(1);
	this->player4->setScale(1);
	this->option_player_one->setScale(1.5);
	this->option_AI_1->setScale(1.5);
	this->option_player_two->setScale(1.5);
	this->option_AI_2->setScale(1.5);
	this->option_player_three->setScale(1.5);
	this->option_AI_3->setScale(1.5);
	this->option_player_four->setScale(1.5);
	this->option_AI_4->setScale(1.5);
	
	
	//this->test->setScale(1);
	//this->option_one_AI->setScale(0);
	//this->option_two_AI->setScale(0);
	//this->option_three_AI->setScale(0);
	//this->option_one_player->setScale(0);
	//this->option_two_player->setScale(0);
	//this->option_three_player->setScale(0);

}
void BeginScene::refresh_menu(Ref* pSender)
{
	this->option1->setScale(0);
	this->option2->setScale(0);
	this->option3->setScale(0);
	this->option_back->setPosition(ccp(150, 100));
	this->option_back->setScale(1.5);


}
void BeginScene::startGame(Ref* pSender,Scene* start_scene, bool online)
{
	auto scene = HelloWorld::create();
	scene->online = online;
	scene->is_advance_mode = this->advance_mode;
	scene->update(0.1);
	for (int i = 0; i < 4; i++) {
		scene->players[i] = this->player[i];
	}
	scene->setPlane();
	auto tran = TransitionFade::create(0.5, scene);
	Director::getInstance()->replaceScene(tran);

}