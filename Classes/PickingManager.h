#ifndef PIKING_MANAGER_H_
#define PIKING_MANAGER_H_

#include "cocos2d.h"
//#include "TemplateSingleton.h"
//#include <list>

//using namespace std;

class CPickingManager : public cocos2d::Node {
public:
	CPickingManager();
	virtual ~CPickingManager();
	virtual bool init();
	CREATE_FUNC(CPickingManager);
	//list<cocos2d::EventMouse*>* eventlist;

private:
	void on_mouse_up(cocos2d::Event*);
	/*void on_mouse_down(cocos2d::Event*);
	void on_mouse_move(cocos2d::Event*);
	void on_mouse_scroll(cocos2d::Event*);*/
};

#endif
