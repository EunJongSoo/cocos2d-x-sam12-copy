#ifndef UNIT_SPRITE_H_
#define UNIT_SPRITE_H_

#include "cocos2d.h"
#include <vector>

class CUnitSprite : public cocos2d::Sprite {
public:
	typedef enum action_list {
		idle,
		blinking,
		move,
		move_up,
		move_down,
		move_left,
		move_right,
		move_up_left,
		move_up_right,
		move_down_left,
		move_down_right,
		attacking,
		die,
		count
	} ActionTag;

	virtual ~CUnitSprite();
	virtual bool init();
	CREATE_FUNC(CUnitSprite);
	
	//void run_action_animate(const int _action);
	//void stop_action_animate();
	void run_action_move_unit(const std::vector<cocos2d::Vec2*>& _vector);
	void auto_targeting_unit(CUnitSprite* const _unit);
	void targeting_unit(CUnitSprite* const _unit);
	void attact_unit(CUnitSprite* const _unit);
	void hit(const int _attack);

	inline const bool is_detected(const cocos2d::Vec2& _vec2, const float _range) const;

private:
	virtual void update(float _dt);
	void move_unit();
	void check_move_action(const cocos2d::Vec2& _dir);
	void goal_target_pos();
	void set_action_tag(const ActionTag _tag);

	void run_action_blinking();
	
	CUnitSprite* target_unit;
	std::vector<cocos2d::Vec2*> move_path_vector;
	cocos2d::Vec2* move_target;

	
	ActionTag action_tag;
	ActionTag move_tag;

	unsigned int frame;

protected:
	CUnitSprite();
	cocos2d::Texture2D* texture[15];
	void update_animation(float _dt);

	unsigned int hp;
	unsigned int attack;
	unsigned int defence;
	float attack_range;
	float attack_speed;
	float move_speed;
};

inline const bool CUnitSprite::is_detected(const cocos2d::Vec2 & _vec2, const float _range) const
{
	return this->getBoundingBox().intersectsCircle(_vec2, _range);
}

#endif