#include "PlayScene.h"

USING_NS_CC;

CPlayScene::CPlayScene() {
}

CPlayScene::~CPlayScene() {
}

bool CPlayScene::init() {
	assert(Scene::init());

	// �� ���̾� �߰�
	ui_layer = CUILayer::create();
	this->addChild(ui_layer, layer_z_order::ui);
	unit_layer = CUnitLayer::create();
	this->addChild(unit_layer, layer_z_order::unit);
	picking_manager = CPickingManager::create();
	this->addChild(picking_manager, layer_z_order::manager);

	// ������ ����
	this->schedule(schedule_selector(CPlayScene::main_update));

	// �ӽ�_���� ��ư �����
	create_menu_close_button();
	


	//// �ӽ� pickingmanager
	auto mouse_listener = EventListenerMouse::create();
	mouse_listener->onMouseUp = CC_CALLBACK_1(CPlayScene::on_mouse_up, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouse_listener, this);

	auto keyboard_listener = EventListenerKeyboard::create();
	keyboard_listener->onKeyPressed = CC_CALLBACK_2(CPlayScene::on_key_pressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard_listener, this);
	
	return true;
}

void CPlayScene::on_mouse_up(Event *_event) {
	// ���콺 �¿� ��ư ������ ���ؼ� ����ȯ
	EventMouse* e = static_cast<EventMouse*>(_event);

	switch (e->getMouseButton()) {
	case MOUSE_BUTTON_LEFT: {

		break;
	}
	case MOUSE_BUTTON_RIGHT: {
		on_mouse_up_right(Point(e->getLocation().x, 640 - e->getLocation().y));
		break;
	}
	}
	// EventMouse���� ��ǥ�� �޾ƿ��� y��ǥ���� �����Ǳ� ������ 
	// y ��ǥ ������ ���� ���� ��ŭ ���༭ Ŭ���� ��ġ�� ã�´�
	
}

void CPlayScene::on_mouse_up_right(const Point &_point) {
	unit_layer->move_sprite(_point);
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
	// uilayer�� �ִ� ������ Ȯ���Ѵ�.
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