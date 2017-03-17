#include "PickingManager.h"

USING_NS_CC;

CPickingManager::CPickingManager()
{
	//eventlist = new list<cocos2d::EventMouse*>;
	//init();
}

CPickingManager::~CPickingManager()
{
	//delete eventlist;
}

bool CPickingManager::init()
{
	assert(Node::init());
	
	// 마우스 이벤트 등록
	auto listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(CPickingManager::on_mouse_up, this);
	//listener->onMouseDown = CC_CALLBACK_1(CPikingManager::on_mouse_down, this);
	//listener->onMouseMove = CC_CALLBACK_1(CPikingManager::on_mouse_move, this);
	//listener->onMouseScroll = CC_CALLBACK_1(CPikingManager::on_mouse_scroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void CPickingManager::on_mouse_up(Event *_event)
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