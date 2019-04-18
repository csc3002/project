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
	int color;                                                 // 0 = 蓝, 1 = 绿, 2 = 红, 3 = 黄
	int id;                                                    // 0-3
	string status;                                             // "ground" = 机场内, "taking off" = 出发点, "outer" = 外圈, "inner" = 终点通路, "finished" = 完成
	string buff;                                               // for extension
	int round_left;                                            // for extension
	int position;                                              // 位置
	int enter_point;                                           // 入外圈点
	int turn_point;                                            // 拐点
	int fly_start;                                             // 虚线起点
	int fly_end;                                               // 虚线终点
	int init_rotation;                                         // 初始机头方向
	int roll;                                                  // 骰子点数
	Vec2 start_point;                                          // 在机场内的坐标
	Vec2 take_off_point;                                       // 出发点坐标
	bool jumped;                                               // 是否已跳跃同颜色格子
	bool can_touch;                                            // 函数onTouchBegan是否生效
    bool _selected = false;
    virtual bool init(int _init_rotation);
	static Planes* create();
	static Planes* create(int _color, int _id, int _enter_point, int _turn_point, int _fly_start, int _fly_end, int _init_rotation, Vec2 _start_point, Vec2 _take_off_point);
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    //CREATE_FUNC(MySprite);
};

#endif // planes_h
