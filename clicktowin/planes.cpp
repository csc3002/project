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

const Vec2 outer[52] = {Vec2(178, 611), Vec2(223, 630), Vec2(266, 630), Vec2(315, 611), Vec2(348, 645), Vec2(331, 694), Vec2(331, 737), Vec2(348, 786), Vec2(394, 801), Vec2(437, 801), Vec2(480, 801), Vec2(523, 801), Vec2(566, 801),
Vec2(611, 782), Vec2(630, 737), Vec2(630, 694), Vec2(611, 645), Vec2(645, 612), Vec2(694, 629), Vec2(737, 629), Vec2(786, 612), Vec2(801, 566), Vec2(801, 523), Vec2(801, 480), Vec2(801, 437), Vec2(801, 394),
Vec2(782, 349), Vec2(737, 330), Vec2(694, 330), Vec2(645, 349), Vec2(612, 315), Vec2(629, 266), Vec2(629, 223), Vec2(612, 174), Vec2(566, 159), Vec2(523, 159), Vec2(480, 159), Vec2(437, 159), Vec2(394, 159),
Vec2(348, 178), Vec2(329, 223), Vec2(329, 266), Vec2(348, 315), Vec2(314, 348), Vec2(265, 331), Vec2(222, 331), Vec2(173, 348), Vec2(158, 394), Vec2(158, 437), Vec2(158, 480), Vec2(158, 523), Vec2(158, 566)};

const Vec2 inner_blue[6] = {Vec2(480, 223), Vec2(480, 266), Vec2(480, 315), Vec2(480, 354), Vec2(480, 396), Vec2(480, 438)};
const Vec2 inner_green[6] = {Vec2(223, 480), Vec2(266, 480), Vec2(315, 480), Vec2(354, 480), Vec2(396, 480), Vec2(438, 480)};
const Vec2 inner_red[6] = {Vec2(480, 737), Vec2(480, 694), Vec2(480, 645), Vec2(480, 606), Vec2(480, 564), Vec2(480, 522)};
const Vec2 inner_yellow[6] = {Vec2(737, 480), Vec2(694, 480), Vec2(645, 480), Vec2(606, 480), Vec2(564, 480), Vec2(522, 480)};

bool Planes::init(int _init_rotation) {
    if (!Sprite::initWithFile("plane.png")) {
        return false;
    }
    setScale(0.102f, 0.102f);
    setRotation(_init_rotation);
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Planes::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}

Planes* Planes::create() {
	Planes * sprite = new Planes();
	if (sprite->init(0)) {
		sprite->autorelease();
	} else {
		delete sprite;
		sprite = NULL;
		return NULL;
	}
	return sprite;
}

Planes* Planes::create(int _color, int _id, int _enter_point, int _turn_point, int _fly_start, int _fly_end, int _init_rotation, Vec2 _start_point, Vec2 _take_off_point) {
    Planes * sprite = new Planes();
    if (sprite->init(_init_rotation)) {
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
		sprite->init_rotation = _init_rotation;
		sprite->roll = 2;
		sprite->start_point = _start_point;
		sprite->take_off_point = _take_off_point;
		sprite->jumped = FALSE;
		sprite->can_touch = TRUE;
	} else {
		delete sprite;
		sprite = NULL;
		return NULL;
	}
	return sprite;
}

bool Planes::onTouchBegan(Touch* touch, Event* event) {
	Vec2 ptClick = touch->getLocation();
	if (this->getBoundingBox().containsPoint(ptClick)) {
		if (can_touch == TRUE) {
			//can_touch = FALSE;
			auto delay = DelayTime::create(0.1f);
			ActionInterval* act[7] = {delay->clone(), delay->clone(), delay->clone(), delay->clone(), delay->clone(), delay->clone(), delay->clone()};
			//cocos2d::log(to_string(roll).c_str());
			int direction = 1; // 1 = 前进, 0 = 终点通路后退
			jumped = FALSE;

			for (int i = 0; i < roll; i++) {
				//if (status == "ground" && roll == 6) {
				if (status == "ground") {
					auto start = MoveTo::create(0.25, take_off_point);
					this->runAction(start);
					status = "taking off";
					break;
				}
				else if (status == "taking off") {
					auto take_off = MoveTo::create(0.25, outer[enter_point]);
					act[i] = take_off->clone();
					status = "outer";
					position = enter_point;
				}
				else if (status == "outer" && position != turn_point) {
					position = (position + 1) % 52;
					auto outer_go = MoveTo::create(0.25, outer[position]);
					act[i] = outer_go->clone();
				}
				else if (position == turn_point) {
					position = 0;
					status = "inner";
					if (color == 0) {
						auto turn = MoveTo::create(0.25, inner_blue[position]);
						act[i] = turn->clone();
					}
					if (color == 1) {
						auto turn = MoveTo::create(0.25, inner_green[position]);
						act[i] = turn->clone();
					}
					if (color == 2) {
						auto turn = MoveTo::create(0.25, inner_red[position]);
						act[i] = turn->clone();
					}
					if (color == 3) {
						auto turn = MoveTo::create(0.25, inner_yellow[position]);
						act[i] = turn->clone();
					}
				}
				else if (status == "inner") {
					//if (position > 4) position = 4;
					if (position == 5) {
						direction = 0;
					}
					if (direction) {
						position++;
					} else {
						position--;
					}
					if (color == 0) {
						auto inner_go = MoveTo::create(0.25, inner_blue[position]);
						act[i] = inner_go->clone();
					}
					if (color == 1) {
						auto inner_go = MoveTo::create(0.25, inner_green[position]);
						act[i] = inner_go->clone();
					}
					if (color == 2) {
						auto inner_go = MoveTo::create(0.25, inner_red[position]);
						act[i] = inner_go->clone();
					}
					if (color == 3) {
						auto inner_go = MoveTo::create(0.25, inner_yellow[position]);
						act[i] = inner_go->clone();
					}
				}

				if (position == 5 && status == "inner" && i == roll - 1) {
					position = -100;
					status = "finished";
					can_touch = FALSE;
					auto finish = MoveTo::create(1, start_point);
					act[6] = finish->clone();
				}
			}

			auto sequence = Sequence::create(act[0], act[1], act[2], act[3], act[4], act[5], act[6], nullptr);
			this->runAction(sequence);
			//auto rotateBy1 = RotateBy::create(0.5,45);
			//this->runAction(rotateBy1);
		}
	}
	return true;
}
