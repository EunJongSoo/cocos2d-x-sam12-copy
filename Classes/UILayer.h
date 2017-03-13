#ifndef UILAYER_H_
#define UILAYER_H_

#include "cocos2d.h"

class CUILayer : public cocos2d::Layer {
public:

	// uilayer에서 정지 변수를 가지고 playscene에서 get함수로 확인하여 사용
	bool get_pause();

	// playscene에서 bool 포인터를 받아와서 사용
	void set_pause(bool *_pause);

	CUILayer();
	~CUILayer();
	virtual bool init();
	CREATE_FUNC(CUILayer);
private:

	bool pause1;
	bool *pause2;
};

#endif

