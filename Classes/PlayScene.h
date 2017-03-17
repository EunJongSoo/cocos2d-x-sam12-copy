#ifndef PLAY_SCENE_H_
#define PLAY_SCENE_H_

#include "cocos2d.h"
#include "UnitLayer.h"
#include "UILayer.h"
#include "PickingManager.h"


class CPlayScene : public cocos2d::Scene {
public:
	CPlayScene();
	~CPlayScene();
	virtual bool init();
	CREATE_FUNC(CPlayScene);

private:
	// 레이어별 위치 지정
	enum layer_z_order{
		unit, ui, manager
	};
	void main_update(float _dt);
	bool check_pasue();

	void create_menu_close_button();
	void menu_close_callback(cocos2d::Ref* pSender);
	
	CUnitLayer *unit_layer;				// 유닛 관리 레이어
	CUILayer *ui_layer;					// UI 관리 레이어
	CPickingManager *picking_manager;	// PikingManager
	//--------------------------------------------------
	void on_mouse_up(cocos2d::Event *_event);
	void on_mouse_up_right(const cocos2d::Point &_point);
	void on_key_pressed(cocos2d::EventKeyboard::KeyCode _code, cocos2d::Event *_event);
	void on_key_pressed_esc();
	//--------------------------------------------------
};


#endif