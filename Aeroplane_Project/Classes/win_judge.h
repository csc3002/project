//
//  win_judge.h
//  Aeroplane_Project
//
//  Created by Re-Entry on 2019/5/5.
//

#ifndef win_judge_h
#define win_judge_h

#include "cocos2d.h"
USING_NS_CC;

class Win_Judge: public cocos2d::Sprite {
public:
    int finishStatusArray[4];                              // whether the plane has finished, 0 = not finished, 1 = finished

    virtual bool init();

    static Win_Judge* create();

    virtual void setFinishStatusArray(EventCustom* event);

    virtual void endGame(int play_win_num);
};

#endif // win_judge_h
