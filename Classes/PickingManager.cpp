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
	
	// ���콺 �̺�Ʈ ���
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
	// ���콺 �¿� ��ư ������ ���ؼ� ����ȯ
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