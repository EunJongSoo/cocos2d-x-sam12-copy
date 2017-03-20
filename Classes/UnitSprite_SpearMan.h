#ifndef SPEAR_MAN_H_
#define SPEAR_MAN_H_

#include "UnitSprite.h"

class SpearMan : public CUnitSprite {
public:
	SpearMan();
	virtual ~SpearMan();
	virtual bool init();
	CREATE_FUNC(SpearMan);
};

#endif
