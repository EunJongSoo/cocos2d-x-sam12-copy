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
	// �����̰� ������ ���߱�
	stop_action(move);

	// ������ �׼� �����ϱ�
	if (!move_action_vector.empty()) {
		int size = move_action_vector.size();
		for (int i = 0; i < size; ++i) {
			delete move_action_vector.at(i);
		}
		move_action_vector.clear();
	}

	// ���� ��ġ Ȯ��
	int x = this->getPosition().x;
	int y = this->getPosition().y;
	
	// ���� ��ġ�� ��ǥ ��ġ�� �Ѱܼ� ��ã��
	path_manager->finding_path(x, y, _vec2.x, _vec2.y);

	// �� ã�� ��� ��������
	//vector<PathFindingManager::vec2*> goal_path = path_manager->goal_path;

	// ��ο� ���� �׼� �����
	int size = path_manager->goal_path.size();
	for (int i = 0; i < size; ++i) {
		auto move_to = MoveTo::create(0.01f, Vec2(path_manager->goal_path.back()->x, path_manager->goal_path.back()->y));
		move_action_vector.pushBack(move_to);
		
		delete path_manager->goal_path.back();
		path_manager->goal_path.erase(path_manager->goal_path.end() - 1);
	}

	// tag ���̰� �׼� ����
	Sequence* move_action_seq = Sequence::create(move_action_vector);
	move_action_seq->setTag(move);
	this->runAction(move_action_seq);
}