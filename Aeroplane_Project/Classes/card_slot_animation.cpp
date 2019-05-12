//
//  card_slot_animation.cpp
//  Aeroplane_Project
//
//  Created by Re-Entry on 2019/5/12.
//

#include "card_slot_animation.h"
USING_NS_CC;

// initiate the card slot
bool Card_Slot_Animation::init() {
    if (!Sprite::initWithFile("none.png")) {
        return false;
    }

    // set custom event listeners
    auto animationCallListener = EventListenerCustom::create("animation_call", CC_CALLBACK_1(Card_Slot_Animation::play_animation, this));

    // add listeners to event dispactcher
    _eventDispatcher->addEventListenerWithSceneGraphPriority(animationCallListener, this);
    return true;
}

Card_Slot_Animation* Card_Slot_Animation::create() {
    Card_Slot_Animation* sprite = new Card_Slot_Animation();
    if (sprite->init()) {
        sprite->autorelease();
        sprite->setPosition(Vec2(-100, -100));
        sprite->setScale(0, 0);

        Animation* animation_slot = Animation::create();
        animation_slot->addSpriteFrameWithFile("machinegun.png");
        animation_slot->addSpriteFrameWithFile("protection.png");
        animation_slot->addSpriteFrameWithFile("stopaction.png");
        animation_slot->addSpriteFrameWithFile("neutralize.png");
        animation_slot->setRestoreOriginalFrame(true);
        animation_slot->setDelayPerUnit(0.0001/1);
        animation_slot->setLoops(300);
        AnimationCache::getInstance()->addAnimation(animation_slot, "Slot");
    }
    else {
        delete sprite;
        sprite = NULL;
        return NULL;
    }
    return sprite;
}

void Card_Slot_Animation::play_animation(EventCustom* event) {
    Vec2 card_slot_pts[4] = {Vec2(50, 50), Vec2(50, 910), Vec2(910, 910), Vec2(910, 50)};
    int color = *(int*)event->getUserData();
    setPosition(card_slot_pts[color]);
    setScale(1);
    Animation* animation = AnimationCache::getInstance()->getAnimation("Slot");
    Animate* animate = Animate::create(animation);
    auto scaleTo = ScaleTo::create(0.0f, 0.0f, 0.0f);
    auto seq = Sequence::create(animate, scaleTo, NULL);
    runAction(seq);
}
