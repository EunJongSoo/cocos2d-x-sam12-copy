#include "EffectSprite.h"

using namespace cocos2d;


//0,0
//112,65
//
//112,0
//108,62
//
//0,68 
//102,60
//
//104,68
//94,55
//
//0,128
//92,52
//
//92,128
//87,50
//
//0, 180
//87,50
//
//88, 180
//87,50
//
//0, 232
//82, 48
//
//84, 232
//80, 46
//
//164, 232
//76, 44
//
//0, 280
//70, 41
//
//72,280
//70, 40
//
//144,280
//46,27
//
//192,280
//24,13


EffectSprite::EffectSprite()
{
	
}


EffectSprite::~EffectSprite()
{
}

bool EffectSprite::init() {
	SpriteFrame* sprite0 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(0, 0, 112, 65));
	SpriteFrame* sprite1 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(112, 0, 108, 62));
	SpriteFrame* sprite2 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(0, 68, 102, 60));
	SpriteFrame* sprite3 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(104, 68, 94, 55));
	SpriteFrame* sprite4 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(0, 128, 92, 52));
	SpriteFrame* sprite5 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(92, 128, 87, 50));
	SpriteFrame* sprite6 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(0, 180, 87, 50));
	SpriteFrame* sprite7 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(88, 180, 87, 50));
	SpriteFrame* sprite8 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(0, 232, 82, 48));
	SpriteFrame* sprite9 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(84, 232, 80, 46));
	SpriteFrame* sprite10 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(164, 232, 76, 44));
	SpriteFrame* sprite11 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(0, 280, 70, 41));
	SpriteFrame* sprite12 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(72, 280, 70, 40));
	SpriteFrame* sprite13 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(144, 280, 46, 27));
	SpriteFrame* sprite14 = SpriteFrame::create("effect_sprite/effect_0_1.png", Rect(192, 280, 24, 13));

	

	auto animation = Animation::create();
	animation->addSpriteFrame(sprite0);
	animation->addSpriteFrame(sprite1);
	animation->addSpriteFrame(sprite2);
	animation->addSpriteFrame(sprite3);
	animation->addSpriteFrame(sprite4);
	animation->addSpriteFrame(sprite5);
	animation->addSpriteFrame(sprite6);
	animation->addSpriteFrame(sprite7);
	animation->addSpriteFrame(sprite8);
	animation->addSpriteFrame(sprite9);
	animation->addSpriteFrame(sprite10);
	animation->addSpriteFrame(sprite11);
	animation->addSpriteFrame(sprite12);
	animation->addSpriteFrame(sprite13);
	animation->addSpriteFrame(sprite14);
	animation->setDelayPerUnit(0.02f);
	animation->setLoops(1);

	animate = Animate::create(animation);

	this->setAnchorPoint(Vec2(0.5f, 0.5f));

	return true;
}

void EffectSprite::run_action_animate() {
	this->runAction(animate);
}