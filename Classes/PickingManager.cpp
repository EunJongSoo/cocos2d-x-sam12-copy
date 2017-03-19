#include "PickingManager.h"
#include "PlayScene.h"
#include "UnitLayer.h"
#include "UnitManager.h"
#include "PathFindingManager.h"
#include "EffectSprite.h"

using namespace cocos2d;

PickingManager::PickingManager()
	: play_scene(nullptr), unit_layer(nullptr), ui_layer(nullptr), 
	path_manager(nullptr), unit_manager(nullptr) {}

PickingManager::~PickingManager()
{
	delete unit_manager;
}

bool PickingManager::init()
{
	assert(Node::init());
	
	
	play_scene = static_cast<CPlayScene*>(Director::getInstance()->getRunningScene());
	unit_layer = play_scene->unit_layer;
	ui_layer = play_scene->ui_layer;
	path_manager = play_scene->path_manager;
	unit_manager = new UnitManager();

	win_size = Director::getInstance()->getWinSize();

	// 마우스 이벤트 등록
	auto listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(PickingManager::on_mouse_up, this);
	//listener->onMouseDown = CC_CALLBACK_1(CPikingManager::on_mouse_down, this);
	//listener->onMouseMove = CC_CALLBACK_1(CPikingManager::on_mouse_move, this);
	//listener->onMouseScroll = CC_CALLBACK_1(CPikingManager::on_mouse_scroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// 키보드 이벤트 등록
	auto keyboard_listener = EventListenerKeyboard::create();
	keyboard_listener->onKeyPressed = CC_CALLBACK_2(PickingManager::on_key_pressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard_listener, this);
	
	unit_layer->addChild(unit_manager->create_unit());
	
	return true;
}

void PickingManager::on_mouse_up(Event *_event) {
	// 마우스 좌우 버튼 구분을 위해서 형변환
	EventMouse* e = static_cast<EventMouse*>(_event);

	// EventMouse에서 좌표를 받아오면 y좌표값이 위에서 아래 쪽으로 커지기 때문에 
	// y 좌표 값에서 세로 길이 만큼 빼줘서 클릭한 위치를 찾는다
	Vec2 location = e->getLocation();
	location.y = win_size.height - location.y;

	switch (e->getMouseButton()) {
	case MOUSE_BUTTON_LEFT: {
		on_mouse_up_left(location);
		break;
	}
	case MOUSE_BUTTON_RIGHT: {
		on_mouse_up_right(location);
		break;
	}
	}
}

void PickingManager::on_mouse_up_left(const Vec2& _vec2) {
	// 선택한 유닛 초기화
	clear_selete_unit();
	Vector<Node*> unit_vector = unit_layer->getChildren();
	CUnitSprite* unit = get_unit_sprite(unit_vector, _vec2);
	if (unit != nullptr) 
		unit_manager->selete_unit(unit);
}

CUnitSprite* PickingManager::get_unit_sprite(const Vector<Node*>& _vector, const Vec2& _vec2)
{
	int size = _vector.size();
	for (int i = 0; i < size; ++i) {
		Rect bounding = _vector.at(i)->getBoundingBox();
		if (bounding.containsPoint(_vec2)) {
			return static_cast<CUnitSprite*>(_vector.at(i));
		}
	}
	return nullptr;
}

void PickingManager::on_mouse_up_right(const Vec2& _vec2) {
	EffectSprite* eff = EffectSprite::create();
	unit_layer->addChild(eff);
	eff->setPosition(_vec2);
	eff->run_action_animate();

	unit_manager->move_unit(_vec2);



}


void PickingManager::on_key_pressed(EventKeyboard::KeyCode _code, Event *_event) {
	switch (_code)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE: on_key_pressed_esc(); break;
	}
}

void PickingManager::on_key_pressed_esc() {

}

void PickingManager::clear_selete_unit()
{
	unit_manager->clear_selete_unit();
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