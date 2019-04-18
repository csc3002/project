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
	int enter_point;                                           // ����Ȧ��
	int turn_point;                                            // �յ�
	int fly_start;                                             // �������
	int fly_end;                                               // �����յ�
	int init_rotation;                                         // ��ʼ��ͷ����
	int roll;                                                  // ���ӵ���
	Vec2 start_point;                                          // �ڻ����ڵ�����
	Vec2 take_off_point;                                       // ����������
	bool jumped;                                               // �Ƿ�����Ծͬ��ɫ����
	bool can_touch;                                            // ����onTouchBegan�Ƿ���Ч
    bool _selected = false;
    virtual bool init(int _init_rotation);
	static Planes* create();
	static Planes* create(int _color, int _id, int _enter_point, int _turn_point, int _fly_start, int _fly_end, int _init_rotation, Vec2 _start_point, Vec2 _take_off_point);
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    //CREATE_FUNC(MySprite);
};

#endif // planes_h
