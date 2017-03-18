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

	path_manager = new PathFindingManager(size_x, size_y, size_cell);

	Sprite* sprite = Sprite::create("CloseNormal.png");
	sprite->setPosition(500, 300);
	sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(sprite, 1);

	/*for (int y = 0; y < size_y; ++y) {
		for (int x = 0; x < size_x; ++x) {
			if (map[y][x] == 1) {
				sprite = Sprite::create("CloseSelected.png");
				sprite->setAnchorPoint(Vec2::ZERO);
				sprite->setPosition(x*size_cell, y*size_cell);
				this->addChild(sprite, 2);
			}
		}
	}*/
	return true;
}

void CUnitLayer::move_sprite(const Point& _point)
{
	Vector<Node*> vector = this->getChildren();
	Sprite* sprite = dynamic_cast<Sprite*>(vector.at(0));
	sprite->stopAllActions();

	Point start_point = sprite->getPosition() / size_cell;
	Point end_point = _point / size_cell;
	
	// 길찾기 시작
	int start, end;
	start = clock();
	path_manager->finding_path(start_point.x, start_point.y, end_point.x, end_point.y);
	end = clock();
	CCLOG("finding_path end : %d", end - start);
	
	// move_action 초기화
	move_action_clear();

	// 액션 만들기
	int size = path_manager->goal_path.size();
	for (int i = 0; i < size; ++i) {
		auto move_to = MoveTo::create(0.01f, Vec2(path_manager->goal_path.back()->x, path_manager->goal_path.back()->y));
		move_action.pushBack(move_to);
		path_manager->goal_path_back_erase();
	}
	Sequence* seq = Sequence::create(move_action);
	sprite->runAction(seq);
}

void CUnitLayer::move_action_clear() {
	int size = move_action.size();
	for (int i = 0; i < size; ++i) {
		delete move_action.at(i);
	}
	move_action.clear();
}