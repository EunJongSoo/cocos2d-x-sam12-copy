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
	

	// 길 찾기 매니저 추가
	path_manager = new PathFindingManager(size_x, size_y, size_cell);

	// 스케쥴 동작
	this->schedule(schedule_selector(CPlayScene::main_update));

	// 임시_종료 버튼 만들기
	create_menu_close_button();
	return true;
}

void CPlayScene::add_picking_manager() {
	picking_manager = PickingManager::create();
	this->addChild(picking_manager, layer_z_order::manager);
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
	add_picking_manager();
	//Director::getInstance()->end();
}