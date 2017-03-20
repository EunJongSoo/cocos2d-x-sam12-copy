#pragma once

#include "cocos2d.h"

class SpearManMoveAnimate : public cocos2d::RepeatForever {
public:
	SpearManMoveAnimate(int i) {
		auto animation = cocos2d::Animation::create();
		cocos2d::SpriteFrameCache* spri = cocos2d::SpriteFrameCache::getInstance();
		spri->addSpriteFramesWithFile("grossini-aliases.plist", "grossini-aliases.png");

		char str[32] = { 0, };
		for (int i = 0; i < 14; ++i) {
			sprintf_s(str, sizeof(str), "grossini_dance_%2d.png", i);
			cocos2d::SpriteFrame* sprite = spri->getSpriteFrameByName(str);
			animation->addSpriteFrame(sprite);
		}
		animation->setDelayPerUnit(0.1);
		animation->setLoops(1);
		auto animate = cocos2d::Animate::create(animation);

		initWithAction(animate);
		/*switch (i)
		{
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
		}*/

	}
	~SpearManMoveAnimate() {}

private:
	SpearManMoveAnimate() {}
};