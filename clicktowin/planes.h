//
//  planes.h
//  Aeroplane_Project
//
//  Created by HRBattery on 2019/4/16.
//

#ifndef planes_h
#define planes_h

#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

class Planes: public cocos2d::Sprite {
public:
	int color; // 0 = 蓝, 1 = 绿, 2 = 红, 3 = 黄
	int id; // 0-3
	string status; // "ground"机场, "taking off"出发点, "outer"外圈, "inner"终点通路, "finished"完成
	string buff; // for extension
	int round_left; // for extension
	int position;
	int enter_point;
	int turn_point;
	int fly_start;
	int fly_end;
	Vec2 start_point;
	Vec2 take_off_point;
	bool jumped;
	bool can_touch; // whether onTouchBegan will activate
    bool _selected = false;
    virtual bool init();
	static Planes* create();
	static Planes* create(int _color, int _id, int _enter_point, int _turn_point, int _fly_start, int _fly_end, Vec2 _start_point, Vec2 _take_off_point);
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    //CREATE_FUNC(MySprite);
};

#endif // planes_h
