#include "UnitLayer.h"

USING_NS_CC;

CUnitLayer::CUnitLayer()
{
}

CUnitLayer::~CUnitLayer()
{
	delete path_manager;
}

bool CUnitLayer::init()
{
	assert(Layer::init());

	path_manager = new PathFindingManager();

	Sprite* sprite = Sprite::create("CloseNormal.png");
	sprite->setPosition(500, 300);
	sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(sprite, 1);

	for (int y = 0; y < SIZE_Y; ++y) {
		for (int x = 0; x < SIZE_X; ++x) {
			if (map[y][x] == 1) {
				sprite = Sprite::create("CloseSelected.png");
				sprite->setAnchorPoint(Vec2::ZERO);
				sprite->setPosition(x*SIZE_CELL, y*SIZE_CELL);
				this->addChild(sprite, 2);
			}
		}
	}
	return true;
}

void CUnitLayer::move_sprite(const Point& _point)
{
	Vector<Node*> vector = this->getChildren();
	Sprite* sprite = dynamic_cast<Sprite*>(vector.at(0));
	sprite->stopAllActions();

	Point start_point = sprite->getPosition() / SIZE_CELL;
	Point end_point = _point / SIZE_CELL;
	
	// 길찾기 시작
	path_manager->finding_path(start_point, end_point);

	// move_action 초기화
	move_action_clear();

	// 액션 만들기
	int fori = path_manager->goal_path.size();
	for (int i = 0; i < fori; ++i) {
		auto move_to = MoveTo::create(0.01f, Vec2(path_manager->goal_path.back()->x, path_manager->goal_path.back()->y));
		move_action.pushBack(move_to);
		path_manager->goal_path_back_erase();
	}
	Sequence* seq = Sequence::create(move_action);
	sprite->runAction(seq);
}

void CUnitLayer::move_action_clear() {
	for (int i = 0; i < move_action.size(); ++i) {
		delete move_action.at(i);
	}
	move_action.clear();
}