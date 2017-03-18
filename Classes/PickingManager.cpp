#include "PickingManager.h"

USING_NS_CC;

PickingManager::PickingManager()
{
	//eventlist = new list<cocos2d::EventMouse*>;
	//init();
}

PickingManager::~PickingManager()
{
	//delete eventlist;
}

bool PickingManager::init()
{
	assert(Node::init());
	
	// 마우스 이벤트 등록
	auto listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(PickingManager::on_mouse_up, this);
	//listener->onMouseDown = CC_CALLBACK_1(CPikingManager::on_mouse_down, this);
	//listener->onMouseMove = CC_CALLBACK_1(CPikingManager::on_mouse_move, this);
	//listener->onMouseScroll = CC_CALLBACK_1(CPikingManager::on_mouse_scroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void PickingManager::on_mouse_up(Event *_event)
{
	// 마우스 좌우 버튼 구분을 위해서 형변환
	EventMouse* e = static_cast<EventMouse*>(_event);
	CCLOG("CPickingManager::on_mouse_up Location : %d", 640 - e->getLocation().y);
}

//void CPikingManager::on_mouse_down(Event *_event)
//{
//	EventMouse* e = static_cast<EventMouse*>(_event);
//}
//
//void CPikingManager::on_mouse_move(Event *_event)
//{
//	EventMouse* e = static_cast<EventMouse*>(_event);
//}
//
//void CPikingManager::on_mouse_scroll(Event *_event)
//{
//	EventMouse* e = static_cast<EventMouse*>(_event);
//}




//
//void CUnitLayer::move_sprite(const Point& _point)
//{
//	Vector<Node*> vector = this->getChildren();
//	Sprite* sprite = dynamic_cast<Sprite*>(vector.at(0));
//	sprite->stopAllActions();
//
//	Point start_point = sprite->getPosition() / size_cell;
//	Point end_point = _point / size_cell;
//
//	// 길찾기 시작
//	int start, end;
//	start = clock();
//	path_manager->finding_path(start_point.x, start_point.y, end_point.x, end_point.y);
//	end = clock();
//	CCLOG("finding_path end : %d", end - start);
//
//	// move_action 초기화
//	//move_action_clear();
//
//	//// 액션 만들기
//	//int size = path_manager->goal_path.size();
//	//for (int i = 0; i < size; ++i) {
//	//	auto move_to = MoveTo::create(0.01f, Vec2(path_manager->goal_path.back()->x, path_manager->goal_path.back()->y));
//	//	move_action.pushBack(move_to);
//	//	path_manager->goal_path_back_erase();
//	//}
//	//Sequence* seq = Sequence::create(move_action);
//	//sprite->runAction(seq);
//}