#include "UnitManager.h"

using namespace cocos2d;
using std::vector;

UnitManager::UnitManager() {
}

UnitManager::~UnitManager() {
}

CUnitSprite* UnitManager::create_unit() {
	CUnitSprite* sprite = CUnitSprite::create();
	sprite->setPosition(500, 300);
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	return sprite;
}

void UnitManager::clear_selete_unit() {
	int size = selete_unit_vector.size();
	for (int i = 0; i < size; ++i) {
		selete_unit_vector[i]->stop_action(CUnitSprite::action_list::blinking);
	}
	selete_unit_vector.clear();
}

void UnitManager::selete_unit(CUnitSprite* const _unit) {
	selete_unit_vector.push_back(_unit);
	blinking_selete_unit();
}

void UnitManager::blinking_selete_unit() {
	int size = selete_unit_vector.size();
	for (int i = 0; i < size; ++i) {
		selete_unit_vector[i]->run_action_animate(CUnitSprite::action_list::blinking);
	}
}

void UnitManager::move_unit(const Vec2& _vec2) {
	int size = selete_unit_vector.size();
	for (int i = 0; i < size; ++i) {
		//selete_unit_vector[i]->run_action_move_unit(_vec2);


		//Vec2 start_pos = selete_unit_vector[i]->getPosition();



	}
}