#include "PlayScene.h"

USING_NS_CC;

CPlayScene::CPlayScene() : pause(true)
{
}

CPlayScene::~CPlayScene()
{
}

bool CPlayScene::init()
{
	assert(Scene::init());

	ui_layer = CUILayer::create();
	ui_layer->set_pause(&pause);
	this->addChild(ui_layer, layer_z_order::ui);

	unit_layer = CUnitLayer::create();
	this->addChild(unit_layer, layer_z_order::unit);
	


	this->schedule(schedule_selector(CPlayScene::main_update));



	// helloworld에 있던 종료버튼 그대로 사용
	// -----------------------------------------------------------------------------------------------
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CPlayScene::menu_close_callback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	// -----------------------------------------------------------------------------------------------

	return true;
}

// helloworld에 있던 종료버튼 그대로 사용
// -----------------------------------------------------------------------------------------------
void CPlayScene::menu_close_callback(Ref* pSender)
{
	Director::getInstance()->end();
}
// -----------------------------------------------------------------------------------------------

void CPlayScene::main_update(float _dt)
{

	// 게임이 정지 되었으면 이후 행동을 하지 않는다.
	// playscene에서 가지고 있는 변수를 확인한다.
	if (pause) return;

	// uilayer에 있는 변수를 확인한다.
	if (check_pasue()) return;

}

bool CPlayScene::check_pasue()
{
	return ui_layer->get_pause();
}
