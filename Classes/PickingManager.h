#ifndef PIKING_MANAGER_H_
#define PIKING_MANAGER_H_

#include "cocos2d.h"
//#include "TemplateSingleton.h"
//#include <list>

//using namespace std;

class PickingManager : public cocos2d::Node {
public:
	PickingManager();
	virtual ~PickingManager();
	virtual bool init();
	CREATE_FUNC(PickingManager);
	//list<cocos2d::EventMouse*>* eventlist;

private:
	void on_mouse_up(cocos2d::Event*);
	/*void on_mouse_down(cocos2d::Event*);
	void on_mouse_move(cocos2d::Event*);
	void on_mouse_scroll(cocos2d::Event*);*/
};

#endif
