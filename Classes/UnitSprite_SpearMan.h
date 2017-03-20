#ifndef SPEAR_MAN_H_
#define SPEAR_MAN_H_

#include "UnitSprite.h"

class SpearMan : public CUnitSprite {
public:
	SpearMan();
	virtual ~SpearMan();
	virtual bool init();
	CREATE_FUNC(SpearMan);

private:
	virtual void run_action_move() override;
	virtual void run_action_attacking() override;
	virtual void run_action_die() override;
};

#endif
