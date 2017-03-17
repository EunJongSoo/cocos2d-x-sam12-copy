#include "PathFindingManager.h"

USING_NS_CC;

PathFindingManager::PathFindingManager() {}
PathFindingManager::~PathFindingManager() {}

void PathFindingManager::goal_path_back_erase() {
	if (!goal_path.empty()) {
		int idx = 1;
		delete goal_path.back();
		goal_path.erase(goal_path.end() - idx);
	}
}

void PathFindingManager::init_path()
{
	for (int i = 0; i < open_path.size(); ++i) {
		delete open_path[i];
	}
	open_path.clear();
	for (int i = 0; i < close_path.size(); ++i) {
		delete close_path[i];
	}
	close_path.clear();
	for (int i = 0; i < close_path.size(); ++i) {
		delete goal_path[i];
	}
	goal_path.clear();
}

void PathFindingManager::finding_path(const Point& _start_point, const Point& _end_point) {
	init_path();

	start_path = new Path(_start_point.x, _start_point.y, 0);
	end_path = new Path(_end_point.x, _end_point.y, 0);

	start_path->g = 0;
	start_path->h = start_path->manhattan_distance(end_path);

	open_path.push_back(start_path);

	// �� ã�� ��
	while (!finding_process());
	// �� ã�� �����ϸ� ~
}

bool PathFindingManager::finding_process() {
	Path* path = search_next_path();
	// ���� path�� ������ ���� �˻��մϴ�.
	if (is_destination_arrival(path)) {
		return true;
	}
	// ���� �������� �ֺ� �˻�
	search_around_path(path);
	return false;
}

Path* PathFindingManager::search_next_path() {
	// open_path�� ������� nullptr�� ��ȯ�մϴ�.
	if (open_path.empty()) return nullptr;

	// �ӽ÷� f�� ū ���� �ְ� open_path�� �ִ� �� �߿��� ���� ���� ���� ã���ϴ�.
	float best_f = 9999999.0f;
	int location = 0;
	for (int i = 0; i < open_path.size(); ++i) {
		if (open_path[i]->get_f() < best_f) {
			best_f = open_path[i]->get_f();
			location = i;
		}
	}
	// ���� f���� ���� path�� close_path�� ����ϰ�, open_path���� ���ݴϴ�.
	close_path.push_back(open_path[location]);
	open_path.erase(open_path.begin() + location);

	// �������� ��ϵ� ���� ��ȯ �մϴ�.
	return close_path.back();
}

bool PathFindingManager::is_destination_arrival(Path* path) {
	if (end_path->index == path->index) {
		end_path->parent = path->parent;
		Path* get_path;
		// ������ �̸� ���������� ������ ���� ��θ� �����մϴ�.
		for (get_path = end_path; get_path != NULL; get_path = get_path->parent) {
			goal_path.push_back(new Vec2(get_path->x * SIZE_CELL, get_path->y * SIZE_CELL));
		}
		return true;
	}
	return false;
}

void PathFindingManager::search_around_path(Path* path) {
	// �ֺ� ��ǥ�� �˻��ϰ�, ���ǿ� ������ open_path�� �߰��Ѵ�.
	path_value tmp_value;
	int tx = 0, ty = 0, index = 0;
	for (int i = 0; i < Direction::dir_count; ++i) {
		tmp_value.set_value(i);
		tx = path->x + tmp_value.x;
		ty = path->y + tmp_value.y;
		index = ty * SIZE_X + tx;
		// �� �� �Ǵ� close_path �̸� �߰����� �ʴ´�.
		if (is_out_bounds(tx, ty) || is_close_path(index)) continue;
		

		// *************** ���� ���� ������ �˻��ؾ��Ѵ�. ***************
		//if (map[ty][tx] == 1) continue;


		path_open(tx, ty, tmp_value.cost, path);
	}
}


bool PathFindingManager::is_out_bounds(float x, float y) {
	// ��ǥ���� �� ���̸� ture, �����̸� false�� ��ȯ�Ѵ�.
	if (x < 0 || x >= SIZE_X || y < 0 || y >= SIZE_Y) {
		return true;
	}
	return false;
}


bool PathFindingManager::is_close_path(int _index) {
	// close_path�� ��ϵǾ����� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	for (int i = 0; i < close_path.size(); ++i) {
		if (_index == close_path[i]->index) {
			return true;
		}
	}
	return false;
}


void PathFindingManager::path_open(int _tx, int _ty, int _cost, Path* _parent) {
	// path�� ��� opne_path�� ������ش�.
	// �� �̹� ��ϵ� path�� ����� �� ���ش�.
	Path* new_path = new Path(_tx, _ty, _parent);
	new_path->g = _cost;
	new_path->h = new_path->manhattan_distance(end_path);
	for (int i = 0; i < open_path.size(); ++i) {
		if (new_path->index == open_path[i]->index) {
			// path_value �� ������ �����ϸ� open_path�� �߰����� �ʰ� �Լ��� �ߴ��Ѵ�.
			if (!update_path_value(new_path, _cost, i)) return;
		}
	}
	// �� ���濡 �����ϰų� ��ϵ��� �ʾҴٸ� open_path�� �߰� �Ѵ�.
	open_path.push_back(new_path);
}


bool PathFindingManager::update_path_value(Path* _path, int _cost, int i) {
	// g ���� ���ؼ� �� ���ٸ� g ���� parent�� �����ϰ� true�� ��ȯ
	float new_f = _path->g + _cost + open_path[i]->h;
	if (new_f < open_path[i]->get_f()) {
		open_path[i]->g = _path->g + _cost;
		open_path[i]->parent = _path;
		return true;
	}
	// �ƴ϶�� �Ҵ��� �����ϰ� flase�� ��ȯ�Ѵ�.
	else {
		delete _path;
		return false;
	}
}