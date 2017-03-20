#include "UnitSprite_SpearMan.h"

using namespace cocos2d;

SpearMan::SpearMan() {}

SpearMan::~SpearMan() {
}

bool SpearMan::init() {

	TextureCache* cache = Director::getInstance()->getTextureCache();
	char str[32] = { 0, };
	for (int i = 0; i < 15; ++i) {
		sprintf_s(str, sizeof(str), "grossini_dance_%d.png", i);
		texture[i] = cache->addImage(str);
	}
	this->initWithFile("grossini_dance_0.png");
		
	hp;
	attack;
	defence;
	attack_range;
	attack_speed;
	move_speed;

	this->schedule(schedule_selector(SpearMan::update_animation), 0.1f);

	return true;
}