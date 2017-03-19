#include "UnitSprite.h"
#include "BlinkingAnimate.h"

using namespace cocos2d;

CUnitSprite::CUnitSprite() 
	: action_animate(nullptr), target_unit(nullptr), move_target(nullptr), 
	move_path_vector(NULL), action_tag(none),
	hp(10), attack(2), defence(1), attack_range(1.0f), attack_speed(1.0f), move_speed(4.0f) {}

CUnitSprite::~CUnitSprite() {
}

bool CUnitSprite::init() {
	assert(Sprite::init());

	this->initWithFile("CloseNormal.png");
	
	return true;
}

void CUnitSprite::run_action_animate(const int _action) {
	set_action_animate(_action);
	//this->runAction(action_animate);
}

void CUnitSprite::set_action_animate(const int _action) {
	if (action_animate != nullptr)
		delete action_animate;
	switch (_action) {
	case action_list::blinking: run_action_blinking(); break;
	case action_list::attacking: run_action_attacking(); break;
	case action_list::move: run_action_move(); break;
	case action_list::die: run_action_die();  break;
	}
}

// stop_action 부분 수정 필요함 임시 작성상태
void CUnitSprite::stop_action() {
	this->stopActionByTag(action_tag);
	action_tag = none;

	// 임시 작성부분
	FadeIn* fade_in = FadeIn::create(0.3f);
	this->runAction(fade_in);
}

void CUnitSprite::run_action_move_unit(const std::vector<Vec2*>& _vector) {
	// 이동 경로 복사
	move_path_vector = _vector;
	
	// 처음 목표 지점 대입
	move_target = move_path_vector.back();
	
	// vector에서 제거
	move_path_vector.pop_back();
	
	// 액션 태그 설정
	action_tag = move;

	// 이동 스케쥴 동작 시작
	this->scheduleUpdate();
}

// 자동 타겟은 현재 타겟이 없을때만 설정된다.
void CUnitSprite::auto_targeting_unit(CUnitSprite * const _unit) {
	if (target_unit != nullptr) {
		targeting_unit(_unit);
	}
}

// 수동 타겟은 언제든 변경된다.
void CUnitSprite::targeting_unit(CUnitSprite * const _unit) {
	target_unit = _unit;
}

void CUnitSprite::attact_unit(CUnitSprite * const _unit) {
	if (_unit->is_detected(_position, attack_range)) {
		_unit->hit(attack);
	}
}

void CUnitSprite::hit(const int _attack) {
	hp -= (defence - _attack);
	if (hp <= 0) {
		hp = 0;
		run_action_animate(die);
	}
}

void CUnitSprite::update(float _dt) {
	// 조건 점검 필요
	if (action_tag < move && action_tag > move_down_right) return;
	goal_target_pos();

	if (move_target != nullptr) {
		Vec2 direction = (*move_target) - _position;
		direction.normalize();

		// ********** 액션 동작 ***********
		this->setPosition(_position + (direction * move_speed));
	}
	else {
		this->unscheduleUpdate();
	}
}

void CUnitSprite::check_move_action(const cocos2d::Vec2 & _dir) {
	if (_dir.y > 0) {
		if (_dir.x > 0)			action_tag = action_list::move_up_right;
		else if (_dir.x < 0)	action_tag = action_list::move_up_left;
		else					action_tag = action_list::move_up;
	}
	else if (_dir.y < 0) {
		if (_dir.x > 0)			action_tag = action_list::move_down_right;
		else if (_dir.x < 0)	action_tag = action_list::move_down_left;
		else					action_tag = action_list::move_down;
	}
	else {
		if (_dir.x > 0)			action_tag = action_list::move_right;
		else if (_dir.x < 0)	action_tag = action_list::move_left;
	}
}

void CUnitSprite::goal_target_pos() {
	Rect bounding = this->getBoundingBox();
	if (bounding.containsPoint(*move_target)) {
		delete move_target;
		if (move_path_vector.size() > 0) {
			move_target = move_path_vector.back();
			move_path_vector.pop_back();
		}
		else {
			move_target = nullptr;
		}
	}
}

void CUnitSprite::run_action_blinking() {
	//action_animate = new BlinkingAnimate();
	//action_animate->setTag(blinking);
	//action_tag = blinking;
}