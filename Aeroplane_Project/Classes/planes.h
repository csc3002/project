//
//  planes.h
//  Aeroplane_Project
//
//  Created by HRBattery on 2019/4/16.
//

#ifndef planes_h
#define planes_h

#include "cocos2d.h"
USING_NS_CC;
class Planes : public cocos2d::Sprite {
public:
    bool _selected = false;
    virtual bool init();
    static Planes* create();
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    bool ccTouchBegan(Touch* pTouch, Event* pEvent);
    //CREATE_FUNC(MySprite);
    
};

#endif /* planes_h */
