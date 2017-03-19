#include "UnitSprite.h"
#include "BlinkingAnimate.h"

using namespace cocos2d;

CUnitSprite::CUnitSprite():
	action_animate(nullptr), move_target(NULL),
	hp(10), attack(1), defence(1), attack_speed(1.0f), move_speed(1.0f)
{

	
}

CUnitSprite::~CUnitSprite() {
}

bool CUnitSprite::init()
{
	assert(Sprite::init());

	this->initWithFile("CloseNormal.png");
	
	return true;
}

void CUnitSprite::set_action_animate(const int _action)
{
	if (action_animate != nullptr)
		delete action_animate;
	switch (_action) {
	case blinking: {
		action_animate = new BlinkingAnimate();
		action_animate->setTag(blinking);
		break;
	}
	}
}

void CUnitSprite::run_action_animate(const int _action) {
	set_action_animate(_action);
	this->runAction(action_animate);
}


// stop_action �κ� ���� �ʿ��� �ӽ� �ۼ�����
void CUnitSprite::stop_action(const int _action) {
	this->stopActionByTag(_action);
	FadeIn* fade_in = FadeIn::create(0.3f);
	this->runAction(fade_in);
}

void CUnitSprite::run_action_move_unit(const std::vector<Vec2*>& _vector) {
	// �̵� ��� ����
	move_path_vector = _vector;
	// ó�� ��ǥ ���� ����
	move_target = (*move_path_vector.back());
	// ������ ��ǥ �����Ҵ� ����
	delete move_path_vector.back();
	// vector���� ����
	move_path_vector.pop_back();
	// �̵� ������ ���� ����
	this->scheduleUpdate();
}

void CUnitSprite::update(float _dt) {
	goal_target_pos();
	if (move_target != NULL) {
		Vec2 pos = _position - move_target;
		Vec2 move_vec2 = pos * _dt * move_speed;
		_position += move_vec2;
	}
	else {
		this->unscheduleUpdate();
	}
}

void CUnitSprite::goal_target_pos() {
	Rect bounding = this->getBoundingBox();
	if (bounding.containsPoint(move_target)) {
		delete move_path_vector.back();
		move_path_vector.pop_back();
		if (move_path_vector.size() > 0)
			move_target = (*move_path_vector.back());
		else {
			move_target = NULL;
		}
	}
}

void CUnitSprite::attack_unit(CUnitSprite * const _unit) {

	_unit->hp = 10;

}