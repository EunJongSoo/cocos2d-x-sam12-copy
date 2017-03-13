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



	// helloworld�� �ִ� �����ư �״�� ���
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

// helloworld�� �ִ� �����ư �״�� ���
// -----------------------------------------------------------------------------------------------
void CPlayScene::menu_close_callback(Ref* pSender)
{
	Director::getInstance()->end();
}
// -----------------------------------------------------------------------------------------------

void CPlayScene::main_update(float _dt)
{

	// ������ ���� �Ǿ����� ���� �ൿ�� ���� �ʴ´�.
	// playscene���� ������ �ִ� ������ Ȯ���Ѵ�.
	if (pause) return;

	// uilayer�� �ִ� ������ Ȯ���Ѵ�.
	if (check_pasue()) return;

}

bool CPlayScene::check_pasue()
{
	return ui_layer->get_pause();
}
