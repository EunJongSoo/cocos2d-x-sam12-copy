#ifndef PLAY_SCENE_H_
#define PLAY_SCENE_H_

#include "cocos2d.h"
#include "UnitLayer.h"
#include "UILayer.h"


class CPlayScene : public cocos2d::Scene {
public:
	

	
	CPlayScene();
	~CPlayScene();
	virtual bool init();
	CREATE_FUNC(CPlayScene);
private:
	// 레이어별 위치 지정
	enum layer_z_order{
		unit, ui,
	};
	void main_update(float _dt);
	bool check_pasue();

	void menu_close_callback(cocos2d::Ref* pSender);
	
	// 유닛 관리 레이어
	CUnitLayer *unit_layer;

	// 시간 관리 레이어

	// UI 관리 레이어
	CUILayer *ui_layer;

	// 게임 정지 변수
	bool pause;
};


#endif