#include "UnitSprite_SpearMan.h"
#include "SpearManMoveAnimate.h"

SpearMan::SpearMan() {
}

SpearMan::~SpearMan() {
}

bool SpearMan::init() {
	return true;
}

void SpearMan::run_action_move() {
	action_animate = new SpearManMoveAnimate(action_tag);
	action_animate->setTag(action_tag);
}

void SpearMan::run_action_attacking() {
	action_tag = action_list::attacking;
}

void SpearMan::run_action_die() {
	action_tag = action_list::die;
}
