#include "UILayer.h"

USING_NS_CC;

bool CUILayer::get_pause()
{
	return pause1;
}

void CUILayer::set_pause(bool * _pause)
{
	pause2 = _pause;
}

CUILayer::CUILayer()
{
}

CUILayer::~CUILayer()
{
}

bool CUILayer::init()
{
	assert(Layer::init());

	return true;
}
