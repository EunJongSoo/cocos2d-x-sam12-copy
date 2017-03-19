#pragma once

#include "cocos2d.h"

class BlinkingAnimate : public cocos2d::RepeatForever {
public:
	BlinkingAnimate() {
		cocos2d::Blink* blink = cocos2d::Blink::create(0.1f, 1);
		initWithAction(blink);
	}
	~BlinkingAnimate() {}
};