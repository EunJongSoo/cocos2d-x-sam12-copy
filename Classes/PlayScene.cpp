#include "PlayScene.h"
#include "PickingManager.h"
#include "PathFindingManager.h"
#include "UnitManager.h"

using namespace cocos2d;

CPlayScene::CPlayScene() {
}

CPlayScene::~CPlayScene() {
	delete path_manager;
}

bool CPlayScene::init() {
	assert(Scene::init());

	// 각 레이어 추가
	ui_layer = CUILayer::create();
	this->addChild(ui_layer, layer_z_order::ui);
	unit_layer = CUnitLayer::create();
	this->addChild(unit_layer, layer_z_order::unit);
	picking_manager = PickingManager::create();
	this->addChild(picking_manager, layer_z_order::manager);

	// 스케쥴 동작
	this->schedule(schedule_selector(CPlayScene::main_update));




	// 임시_종료 버튼 만들기
	create_menu_close_button();


	////
	path_manager = new PathFindingManager(size_x, size_y, size_cell);
	unit_manager = new UnitManager();
	unit_layer->addChild(unit_manager->create_unit(), 1, 1);
	////

	//// 임시 picking
	auto mouse_listener = EventListenerMouse::create();
	mouse_listener->onMouseUp = CC_CALLBACK_1(CPlayScene::on_mouse_up, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouse_listener, this);

	auto keyboard_listener = EventListenerKeyboard::create();
	keyboard_listener->onKeyPressed = CC_CALLBACK_2(CPlayScene::on_key_pressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard_listener, this);
	
	return true;
}

void CPlayScene::on_mouse_up(Event *_event) {
	// 마우스 좌우 버튼 구분을 위해서 형변환
	EventMouse* e = static_cast<EventMouse*>(_event);

	switch (e->getMouseButton()) {
	case MOUSE_BUTTON_LEFT: {
		on_mouse_up_left(Vec2(e->getLocation().x, 640 - e->getLocation().y));
		break;
	}
	case MOUSE_BUTTON_RIGHT: {
		on_mouse_up_right(Vec2(e->getLocation().x, 640 - e->getLocation().y));
		break;
	}
	}
	// EventMouse에서 좌표를 받아오면 y좌표값이 반전되기 때문에 
	// y 좌표 값에서 세로 길이 만큼 빼줘서 클릭한 위치를 찾는다
	
}
void CPlayScene::on_mouse_up_left(const Vec2& _vec2) {
	unit_manager->clear_selete_unit();
	Vector<Node*> unit_vector = unit_layer->getChildren();
	int size = unit_vector.size();
	for (int i = 0; i < size; ++i) {
		Rect bounding = unit_vector.at(i)->getBoundingBox();
		if (bounding.containsPoint(_vec2)) {
			CUnitSprite* unit = static_cast<CUnitSprite*>(unit_vector.at(i));
			unit_manager->selete_unit(unit);
			break;
		}
	}
}

void CPlayScene::on_mouse_up_right(const Vec2& _vec2) {
	unit_manager->move_unit(_vec2);
}


void CPlayScene::on_key_pressed(EventKeyboard::KeyCode _code, Event *_event) {
	switch (_code)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE: on_key_pressed_esc(); break;
	}
}

void CPlayScene::on_key_pressed_esc() {

}

void CPlayScene::main_update(float _dt) {
	// uilayer에 있는 변수를 확인한다.
	if (check_pasue()) return;
}

bool CPlayScene::check_pasue() {
	return ui_layer->get_pause();
}

void CPlayScene::create_menu_close_button() {
	Size visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto close_item = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CPlayScene::menu_close_callback, this));

	Size item_content_size = close_item->getContentSize();
	close_item->setPosition(Vec2(origin.x + visible_size.width - item_content_size.width / 2, 
		origin.y + item_content_size.height / 2));

	auto menu = Menu::create(close_item, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void CPlayScene::menu_close_callback(Ref* pSender) {
	Director::getInstance()->end();
}