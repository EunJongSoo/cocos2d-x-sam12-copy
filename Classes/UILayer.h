#ifndef UILAYER_H_
#define UILAYER_H_

#include "cocos2d.h"

class CUILayer : public cocos2d::Layer {
public:

	// uilayer���� ���� ������ ������ playscene���� get�Լ��� Ȯ���Ͽ� ���
	bool get_pause();

	// playscene���� bool �����͸� �޾ƿͼ� ���
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

