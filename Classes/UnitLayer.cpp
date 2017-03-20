#include "UnitLayer.h"
#include "PathFindingManager.h"
#include "UnitSprite.h"

using namespace cocos2d;
using std::vector;

CUnitLayer::CUnitLayer() {
	path_manager = new PathFindingManager();
}

CUnitLayer::~CUnitLayer() {}

bool CUnitLayer::init()
{
	assert(Layer::init());
	return true;
}

void CUnitLayer::create_unit() {
	CUnitSprite* sprite = CUnitSprite::create();
	sprite->setPosition(500, 300);
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	unit_vector.push_back(sprite);
	this->addChild(sprite);
}

void CUnitLayer::clear_selete_unit() {
	int size = selete_unit_vector.size();
	for (CUnitSprite* sprite : selete_unit_vector) {
		sprite->stop_action_animate();
	}
	selete_unit_vector.clear();
}

const bool CUnitLayer::selete_unit(const cocos2d::Vec2& _vec2) {
	for (CUnitSprite* sprite : unit_vector) {
		if (sprite->getBoundingBox().containsPoint(_vec2)) {
			selete_unit_vector.push_back(sprite);
			return true;
		}
	}
	return false;
}

void CUnitLayer::blinking_selete_unit() {
	for (CUnitSprite* sprite : selete_unit_vector) {
		sprite->run_action_animate(CUnitSprite::action_list::blinking);
	}
}

// 임시 작성
void CUnitLayer::move_unit(const Vec2& _vec2) {
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