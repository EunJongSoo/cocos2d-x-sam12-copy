#ifndef EFFECT_SPRITE_H_
#define EFFECT_SPRITE_H_

#include "cocos2d.h"

class EffectSprite : public cocos2d::Sprite {
public:
	EffectSprite();
	virtual ~EffectSprite();
	virtual bool init();
	CREATE_FUNC(EffectSprite);
	
	void run_action_animate();

private:
	cocos2d::Animate* animate;

};

#endif
