#ifndef UNIT_LAYER_H_
#define UNIT_LAYER_H_

#include "cocos2d.h"

class CUnitLayer : public cocos2d::Layer {
public:
	CUnitLayer();
	~CUnitLayer();
	virtual bool init();
	CREATE_FUNC(CUnitLayer);
private:
	
};
#endif
