#ifndef UNIT_LAYER_H_
#define UNIT_LAYER_H_

#include "cocos2d.h"
#include "PathFindingManager.h"
#include <vector>

using namespace std;

class CUnitLayer : public cocos2d::Layer {
public:
	void move_sprite(const cocos2d::Point& _point);

	CUnitLayer();
	~CUnitLayer();
	virtual bool init();
	CREATE_FUNC(CUnitLayer);
private:
	const unsigned int size_x = 192;
	const unsigned int size_y = 128;
	const float size_cell = 5.0f;

	/*const unsigned int size_x = 96;
	const unsigned int size_y = 64;
	const float size_cell = 10.0f;*/

	PathFindingManager* path_manager;
	void move_action_clear();

	cocos2d::Vector<cocos2d::FiniteTimeAction*> move_action;
};
#endif
