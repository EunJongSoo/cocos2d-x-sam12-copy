#ifndef PLAY_SCENE_H_
#define PLAY_SCENE_H_

#include "cocos2d.h"
#include "UnitLayer.h"
#include "UILayer.h"

class PickingManager;
class UnitManager;
class PathFindingManager;

class CPlayScene : public cocos2d::Scene {
public:
	CPlayScene();
	~CPlayScene();
	virtual bool init();
	CREATE_FUNC(CPlayScene);

	CUnitLayer *unit_layer;				// 유닛 관리 레이어
	CUILayer *ui_layer;					// UI 관리 레이어

	PickingManager *picking_manager;	// PikingManager
	PathFindingManager* path_manager;
private:
	const unsigned int size_x = 192;
	const unsigned int size_y = 128;
	const float size_cell = 5.0f;

	// 레이어별 위치 지정
	enum layer_z_order{
		unit, ui, manager
	};
	void main_update(float _dt);
	bool check_pasue();
	void add_picking_manager();

	void create_menu_close_button();
	void menu_close_callback(cocos2d::Ref* pSender);

	/*const unsigned int size_x = 96;
	const unsigned int size_y = 64;
	const float size_cell = 10.0f;*/
};


#endif