#ifndef UNIT_MANAGER_H_
#define UNIT_MANAGER_H_

#include <vector>
#include "cocos2d.h"
#include "UnitSprite.h"

class UnitManager {
public:
	UnitManager();
	~UnitManager();

	CUnitSprite* create_unit();
	void clear_selete_unit();
	void selete_unit(CUnitSprite* const _unit);
	void blinking_selete_unit();
	void move_unit(const cocos2d::Vec2& _vec2);

private:
	std::vector<CUnitSprite*> unit_vector;
	std::vector<CUnitSprite*> selete_unit_vector;
};

#endif