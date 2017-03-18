#ifndef UNIT_SPRITE_H_
#define UNIT_SPRITE_H_

#include "cocos2d.h"

class PathFindingManager;
class CUnitSprite : public cocos2d::Sprite {
public:
	enum action_list {
		move, blinking
	};
	CUnitSprite();
	virtual ~CUnitSprite();
	virtual bool init();
	CREATE_FUNC(CUnitSprite);

	void run_action_move_unit(const cocos2d::Vec2& _vec2);
	void run_action_blinking_sprite();
	void stop_action(const int _action);

private:
	cocos2d::RepeatForever* blinking_animate;
	cocos2d::RepeatForever* move_animate;
	cocos2d::RepeatForever* attack_animate;
	cocos2d::Vector<cocos2d::FiniteTimeAction*> move_action_vector;
	
	PathFindingManager* path_manager;
};

#endif