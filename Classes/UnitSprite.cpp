#include "UnitSprite.h"
#include "BlinkingAnimate.h"

using namespace cocos2d;

CUnitSprite::CUnitSprite() 
	: target_unit(nullptr), move_target(nullptr), move_path_vector(NULL), action_tag(idle), move_tag(move),
	hp(10), attack(2), defence(1), attack_range(1.0f), attack_speed(1.0f), move_speed(4.0f) {}

CUnitSprite::~CUnitSprite() {
}

bool CUnitSprite::init() {
	assert(Sprite::init());

	this->initWithFile("CloseNormal.png");
	

	return true;
}

void CUnitSprite::run_action_move_unit(const std::vector<Vec2*>& _vector) {
	// 이동 경로 복사
	move_path_vector = _vector;
	
	// 처음 목표 지점 대입
	move_target = move_path_vector.back();
	
	// vector에서 제거
	move_path_vector.pop_back();
	
	// 태그 설정
	set_action_tag(ActionTag::move);

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
	set_action_tag(ActionTag::attacking);
	int dmg = _attack - defence;
	if (dmg <= 0)
		dmg = 1;
	hp -= dmg;
	if (hp <= 0) {
		hp = 0;
		//run_action_animate(die);
	}
}

void CUnitSprite::update(float _dt) {

	if (action_tag == move) {
		move_unit();
	}
	else {
		this->unscheduleUpdate();
	}
}

void CUnitSprite::update_animation(float _dt) {
	// 조건 점검 필요
	//if (action_tag < move && action_tag > move_down_right) return;
	switch (action_tag)
	{
	case ActionTag::idle: 				break;
	case ActionTag::blinking:				break;
	case ActionTag::attacking:			break;
	case ActionTag::die:					break;
	case ActionTag::move: {
		this->setTexture(texture[frame++]);
		if (frame >= 15) 
			frame = 0;
		break;
	}
	default:
		break;
	}
}

void CUnitSprite::move_unit() {
	goal_target_pos();
	if (move_target != nullptr) {
		Vec2 direction = (*move_target) - _position;
		direction.normalize();
		check_move_action(direction);
		this->setPosition(_position + (direction * move_speed));
	}
	else {
		set_action_tag(ActionTag::idle);
		this->unscheduleUpdate();
	}
}

void CUnitSprite::check_move_action(const cocos2d::Vec2 & _dir) {
	if (_dir.y > 0) {
		move_tag = (_dir.x > 0) ? move_up_right : (_dir.x < 0) ? move_up_left : move_up;
	}
	else if (_dir.y < 0) {
		move_tag = (_dir.x > 0) ? move_down_right : (_dir.x < 0) ? move_down_left : move_down;
	}
	else {
		move_tag = (_dir.x > 0) ? move_right : move_left;
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

void CUnitSprite::set_action_tag(const ActionTag _tag) {
	action_tag = _tag;
	frame = 0;

}

void CUnitSprite::run_action_blinking() {
	//action_animate = new BlinkingAnimate();
	//action_animate->setTag(blinking);
	//action_tag = blinking;
}




//void CUnitSprite::run_action_animate(const int _action) {
//	stop_action_animate();
//	switch (_action) {
//	case action_list::blinking: run_action_blinking(); break;
//	case action_list::attacking: run_action_attacking(); break;
//	case action_list::die: run_action_die();  break;
//		//case action_list::move: run_action_move(); break;
//	}
//}
//
//// stop_action 부분 수정 필요함 임시 작성상태
//void CUnitSprite::stop_action_animate() {
//	//if (action_animate != nullptr) {
//	//	this->stopActionByTag(action_tag);
//	//	delete action_animate;
//	//	action_animate = nullptr;
//	//	action_tag = none;
//
//	//	//액션을 멈추고 대기 상태로 전환하기
//
//	//}
//	//// 임시 작성부분
//	//FadeIn* fade_in = FadeIn::create(0.3f);
//	//this->runAction(fade_in);
//}