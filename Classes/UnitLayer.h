#ifndef UNIT_LAYER_H_
#define UNIT_LAYER_H_

#include <vector>
#include "cocos2d.h"

class CUnitSprite;
class PathFindingManager;
class CUnitLayer : public cocos2d::Layer {
public:
	CUnitLayer();
	~CUnitLayer();
	virtual bool init();
	CREATE_FUNC(CUnitLayer);

	void create_unit();
	void selete_unit(const cocos2d::Vec2& _vec2);
	void move_unit(const cocos2d::Vec2& _vec2);
	void clear_selete_unit();

private:
	std::vector<CUnitSprite*> unit_vector;
	std::vector<CUnitSprite*> selete_unit_vector;
	PathFindingManager* path_manager;
	
};
#endif
