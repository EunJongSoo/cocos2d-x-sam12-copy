#include "UnitManager.h"
#include "PathFindingManager.h"

using namespace cocos2d;
using std::vector;

UnitManager::UnitManager() {
	path_manager = new PathFindingManager();
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
	for (CUnitSprite* sprite : selete_unit_vector) {
		sprite->stop_action();
	}
	selete_unit_vector.clear();
}

void UnitManager::selete_unit(CUnitSprite* const _unit) {
	selete_unit_vector.push_back(_unit);
	blinking_selete_unit();
}

void UnitManager::blinking_selete_unit() {
	for (CUnitSprite* sprite : selete_unit_vector) {
		sprite->run_action_animate(CUnitSprite::action_list::blinking);
	}
}

// 임시 작성
void UnitManager::move_unit(const Vec2& _vec2) {
	vector<Vec2*> vector;
	for (CUnitSprite* sprite : selete_unit_vector) {

		int start, end;
		start = clock();
		path_manager->finding_path(sprite->getPosition().x, sprite->getPosition().y, _vec2.x, _vec2.y);
		end = clock();
		CCLOG("finding_path end : %d", end - start);

		std::vector<PathFindingManager::vec2*>& tmpvector = path_manager->goal_path;
		for (PathFindingManager::vec2* _vec2 : tmpvector) {
			vector.push_back(new Vec2(_vec2->x, _vec2->y));
		}
		path_manager->goal_path_clear();
		sprite->run_action_move_unit(vector);
	}
}