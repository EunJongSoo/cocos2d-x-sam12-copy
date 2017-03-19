#ifndef UNIT_SPRITE_H_
#define UNIT_SPRITE_H_

#include "cocos2d.h"
#include <vector>

class CUnitSprite : public cocos2d::Sprite {
public:
	enum action_list {
		blinking, attacking
	};
	CUnitSprite();
	virtual ~CUnitSprite();
	virtual bool init();
	CREATE_FUNC(CUnitSprite);

	void set_action_animate(const int _action);
	void run_action_animate(const int _action);
	void stop_action(const int _action);
	void run_action_move_unit(const std::vector<cocos2d::Vec2*>& _vector);

	

private:
	virtual void update(float _dt);
	void goal_target_pos();
	void attack_unit(CUnitSprite* const _unit);

	
	cocos2d::Vec2 move_target;
	cocos2d::RepeatForever* action_animate;
	std::vector<cocos2d::Vec2*> move_path_vector;

	unsigned int hp;
	unsigned int attack;
	unsigned int defence;
	float attack_speed;
	float move_speed;
};

#endif