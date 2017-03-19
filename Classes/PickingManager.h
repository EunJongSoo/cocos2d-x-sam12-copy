#ifndef PIKING_MANAGER_H_
#define PIKING_MANAGER_H_

#include "cocos2d.h"

class CPlayScene;
class CUnitLayer;
class CUILayer;
class CUnitSprite;
class UnitManager;
class PathFindingManager;

class PickingManager : public cocos2d::Node {
public:
	PickingManager();
	virtual ~PickingManager();
	virtual bool init();
	CREATE_FUNC(PickingManager);

private:
	void on_mouse_up(cocos2d::Event *_event);
	void on_mouse_up_left(const cocos2d::Vec2& _vec2);
	void on_mouse_up_right(const cocos2d::Vec2 &_point);
	void on_key_pressed(cocos2d::EventKeyboard::KeyCode _code, cocos2d::Event *_event);
	void on_key_pressed_esc();

	void clear_selete_unit();
	CUnitSprite* get_unit_sprite(const cocos2d::Vector<cocos2d::Node*>& _vector, const cocos2d::Vec2& _vec2);
	/*void on_mouse_down(cocos2d::Event*);
	void on_mouse_move(cocos2d::Event*);
	void on_mouse_scroll(cocos2d::Event*);*/

	CPlayScene* play_scene;
	CUnitLayer* unit_layer;
	CUILayer* ui_layer;

	UnitManager* unit_manager;
	PathFindingManager* path_manager;

	cocos2d::Size win_size;
};

#endif
