#include "UnitSprite.h"
#include "PathFindingManager.h"

using namespace cocos2d;

CUnitSprite::CUnitSprite() {
}

CUnitSprite::~CUnitSprite() {
}

bool CUnitSprite::init()
{
	assert(Sprite::init());

	this->initWithFile("CloseNormal.png");

	path_manager = new PathFindingManager();

	move_animate;
	attack_animate;


	
	FadeIn* fade_in = FadeIn::create(0.3f);
	FadeOut* fade_out = FadeOut::create(0.3f);
	Sequence* seq = Sequence::create(fade_in, fade_out, NULL);
	blinking_animate = RepeatForever::create(seq);
	blinking_animate->retain();
	blinking_animate->setTag(blinking);

	return true;
}

void CUnitSprite::run_action_blinking_sprite() {
	this->runAction(blinking_animate);
}
void CUnitSprite::stop_action(const int _action) {
	this->stopActionByTag(_action);
	FadeIn* fade_in = FadeIn::create(0.3f);
	this->runAction(fade_in);
}

void CUnitSprite::run_action_move_unit(const Vec2& _vec2) {
	// 움직이고 있으면 멈추기
	stop_action(move);

	// 만들어둔 액션 삭제하기
	if (!move_action_vector.empty()) {
		int size = move_action_vector.size();
		for (int i = 0; i < size; ++i) {
			delete move_action_vector.at(i);
		}
		move_action_vector.clear();
	}

	// 현재 위치 확인
	int x = this->getPosition().x;
	int y = this->getPosition().y;
	
	// 현재 위치와 목표 위치를 넘겨서 길찾기
	path_manager->finding_path(x, y, _vec2.x, _vec2.y);

	// 길 찾은 결과 가져오기
	//vector<PathFindingManager::vec2*> goal_path = path_manager->goal_path;

	// 경로에 맞춰 액션 만들기
	int size = path_manager->goal_path.size();
	for (int i = 0; i < size; ++i) {
		auto move_to = MoveTo::create(0.01f, Vec2(path_manager->goal_path.back()->x, path_manager->goal_path.back()->y));
		move_action_vector.pushBack(move_to);
		
		delete path_manager->goal_path.back();
		path_manager->goal_path.erase(path_manager->goal_path.end() - 1);
	}

	// tag 붙이고 액션 실행
	Sequence* move_action_seq = Sequence::create(move_action_vector);
	move_action_seq->setTag(move);
	this->runAction(move_action_seq);
}