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
	// ���̾ ��ġ ����
	enum layer_z_order{
		unit, ui,
	};
	void main_update(float _dt);
	bool check_pasue();

	void menu_close_callback(cocos2d::Ref* pSender);
	
	// ���� ���� ���̾�
	CUnitLayer *unit_layer;

	// �ð� ���� ���̾�

	// UI ���� ���̾�
	CUILayer *ui_layer;

	// ���� ���� ����
	bool pause;
};


#endif