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
	int color;                                                 // 0 = ��, 1 = ��, 2 = ��, 3 = ��
	int id;                                                    // 0-3
	string status;                                             // "ground" = ������, "taking off" = ������, "outer" = ��Ȧ, "inner" = �յ�ͨ·, "finished" = ���
	string buff;                                               // for extension
	int round_left;                                            // for extension
	int position;                                              // λ��
	int enter_pt;                                              // ����Ȧ��
	int turn_pt;                                               // �յ�
	int fly_start;                                             // �������
	int fly_end;                                               // �����յ�
	int init_rotation;                                         // ��ʼ��ͷ����
	int roll;                                                  // ���ӵ���
	Vec2 start_pt;                                             // �ڻ����ڵ�����
	Vec2 take_off_pt;                                          // ����������
	bool jumped;                                               // �Ƿ�����Ծͬ��ɫ����
	bool can_touch;                                            // ����onTouchBegan�Ƿ���Ч
    bool _selected = false;
    virtual bool init(int _init_rotation);
	static Planes* create();
	static Planes* create(int _color, int _id, int _enter_pt, int _turn_pt, int _fly_start, int _fly_end, int _init_rotation, Vec2 _start_pt, Vec2 _take_off_pt, string _status = "ground", int _position = -1, int _roll = 2);
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void going_down();
    //CREATE_FUNC(MySprite);
};

#endif // planes_h
