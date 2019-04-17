//
//  planes.cpp
//  Aeroplane_Project
//
//  Created by HRBattery on 2019/4/16.
//

#include "planes.h"
#include <string>
USING_NS_CC;
using namespace std;

const Vec2 out[52] = {Vec2(178, 611), Vec2(223, 630), Vec2(266, 630), Vec2(315, 611), Vec2(348, 645), Vec2(331, 694), Vec2(331, 737), Vec2(348, 786), Vec2(394, 801), Vec2(437, 801), Vec2(480, 801), Vec2(523, 801), Vec2(566, 801),
Vec2(611, 782), Vec2(630, 737), Vec2(630, 694), Vec2(611, 645), Vec2(645, 612), Vec2(694, 629), Vec2(737, 629), Vec2(786, 612), Vec2(801, 566), Vec2(801, 523), Vec2(801, 480), Vec2(801, 437), Vec2(801, 394),
Vec2(782, 349), Vec2(737, 330), Vec2(694, 330), Vec2(645, 349), Vec2(612, 315), Vec2(629, 266), Vec2(629, 223), Vec2(612, 174), Vec2(566, 159), Vec2(523, 159), Vec2(480, 159), Vec2(437, 159), Vec2(394, 159),
Vec2(348, 178), Vec2(329, 223), Vec2(329, 266), Vec2(348, 315), Vec2(314, 348), Vec2(265, 331), Vec2(222, 331), Vec2(173, 348), Vec2(158, 394), Vec2(158, 437), Vec2(158, 480), Vec2(158, 523), Vec2(158, 566)};
const Vec2 in_blue[6] = {Vec2(480, 223), Vec2(480, 266), Vec2(480, 315), Vec2(480, 354), Vec2(480, 396), Vec2(480, 438)};
const Vec2 in_green[6] = {Vec2(223, 480), Vec2(266, 480), Vec2(315, 480), Vec2(354, 480), Vec2(396, 480), Vec2(438, 480)};
const Vec2 in_red[6] = {Vec2(480, 737), Vec2(480, 694), Vec2(480, 645), Vec2(480, 606), Vec2(480, 564), Vec2(480, 522)};
const Vec2 in_yellow[6] = {Vec2(737, 480), Vec2(694, 480), Vec2(645, 480), Vec2(606, 480), Vec2(564, 480), Vec2(522, 480)};

bool Planes::init() {
    
    if (!Sprite::initWithFile("plane.png")) {
        return false;
    }

    setScale(0.102f, 0.102f);
    //setRotation(90);
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Planes::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}

Planes* Planes::create() {
	Planes * sprite = new Planes();
	if (sprite->init()) {
		sprite->autorelease();
	}
	else
	{
		delete sprite;
		sprite = NULL;
		return NULL;
	}
	return sprite;
}

Planes* Planes::create(int _color, int _id, int _enter_point, int _turn_point, int _fly_start, int _fly_end, Vec2 _start_point, Vec2 _take_off_point) {
    Planes * sprite = new Planes();
    if (sprite->init()) {
        sprite->autorelease();
		sprite->color = _color;
		sprite->id = _id;
		sprite->status = "ground";
		sprite->buff = "None";
		sprite->round_left = 0;
		sprite->position = -1;
		sprite->enter_point = _enter_point;
		sprite->turn_point = _turn_point;
		sprite->fly_start = _fly_start;
		sprite->fly_end = _fly_end;
		sprite->start_point = _start_point;
		sprite->take_off_point = _take_off_point;
		sprite->jumped = FALSE;
		sprite->can_touch = TRUE;
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
		if (status == "ground") {
			auto moveTo1 = MoveTo::create(0.5, take_off_point);
			this->runAction(moveTo1);
			status = "taking off";
		}
		else if (status == "taking off") {
			auto moveTo2 = MoveTo::create(0.5, out[enter_point]);
			this->runAction(moveTo2);
			status = "outer";
			position = enter_point;
		}
		else if (status == "outer" && position != turn_point) {
			position = (position + 1) % 52;
			auto moveTo3 = MoveTo::create(0.5, out[position]);
			this->runAction(moveTo3);
			if (position == turn_point) {
				position = -1;
				status = "inner";
			}
		}
		else if (status == "inner") {
			position++;
			if (color == 0) {
				auto moveTo4 = MoveTo::create(0.5, in_blue[position]);
				this->runAction(moveTo4);
			}
			if (color == 1) {
				auto moveTo4 = MoveTo::create(0.5, in_green[position]);
				this->runAction(moveTo4);
			}
			if (color == 2) {
				auto moveTo4 = MoveTo::create(0.5, in_red[position]);
				this->runAction(moveTo4);
			}
			if (color == 3) {
				auto moveTo4 = MoveTo::create(0.5, in_yellow[position]);
				this->runAction(moveTo4);
			}
		}
		if (position == 5 && status == "inner") {
			status = "finished";
			auto delay = DelayTime::create(1.2f);
			auto moveTo5 = MoveTo::create(1, start_point);
			auto sequence = Sequence::create(delay, moveTo5, nullptr);
			this->runAction(sequence);
		}
        /*auto rotateBy1 = RotateBy::create(0.5,45);
        auto moveTo1 = MoveTo::create(0.5, Vec2(100,200));
        this->runAction(rotateBy1);
        this->runAction(moveTo1);*/
    }
    return true;
}
