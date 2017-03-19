#include "PathFindingManager.h"
#include "Path.h"

PathFindingManager::PathFindingManager() 
	: start_path(nullptr), end_path(nullptr), size_x(192), size_y(128), size_cell(5.0f)  {

}
PathFindingManager::PathFindingManager(const int _size_x, const int _size_y, const int _size_cell)
	: start_path(nullptr), end_path(nullptr), size_x(_size_x), size_y(_size_y), size_cell(_size_cell) {
}
PathFindingManager::~PathFindingManager() {}

void PathFindingManager::init_path() {
	path_vector_clear(open_path_vector);
	path_vector_clear(close_path_vector);
	goal_path_clear();
}

void PathFindingManager::path_vector_clear(vector<Path*>& _vector) {
	for (Path* path : _vector) {
		delete path;
	}
	_vector.clear();
}

void PathFindingManager::goal_path_clear() {
	for (vec2* vec2 : goal_path) {
		delete vec2;
	}
	goal_path.clear();
}

void PathFindingManager::finding_path(const float _str_x, const float _str_y, 
										const float _end_x, const float _end_y) 
{
	init_path();

	int str_x = _str_x / size_cell;
	int str_y = _str_y / size_cell;
	int end_x = _end_x / size_cell;
	int end_y = _end_y / size_cell;

	start_path = new Path(str_x, str_y, str_y * size_x + str_x, nullptr);
	end_path = new Path(end_x, end_y, end_y * size_x + end_x, nullptr);

	start_path->consumption_cost = 0.0f;
	start_path->expected_cost = start_path->manhattan_distance(end_path);

	open_path_vector.push_back(start_path);

	// �� ã�� ��
	finding_process();
}

void PathFindingManager::finding_process() {
	Path* path;
	while (true) {
		path = search_next_path();
		if (is_goal(path->idx)) break;
		search_around_path(path);
	}
	record_path(path);
}

const bool PathFindingManager::is_goal(const int _idx) const {
	return (end_path->idx == _idx);
}

void PathFindingManager::record_path(const Path* const _path) {
	end_path->set_parent(_path->get_parent());
	Path* get_path;
	// ������ �̸� ���������� ������ ���� ��θ� �����մϴ�.
	for (get_path = end_path; get_path != nullptr; get_path = get_path->get_parent()) {
		goal_path.push_back(new vec2(get_path->x * size_cell, get_path->y * size_cell));
	}
}


Path* PathFindingManager::search_next_path() {
	// �ӽ÷� f�� ū ���� �ְ� open_path�� �ִ� �� �߿��� ���� ���� ���� ã���ϴ�.
	float best_cost = 9999999.0f;
	int location = 0, i = 0;

	for (Path* path : open_path_vector) {
		if (best_cost > path->get_cost()) {
			best_cost = path->get_cost();
			location = i;
		}
		++i;
	}
	// ���� f���� ���� path�� close_path�� ����ϰ�, open_path���� ���ݴϴ�.
	close_path_vector.push_back(open_path_vector[location]);
	open_path_vector.erase(open_path_vector.begin() + location);

	// �������� ��ϵ� ���� ��ȯ �մϴ�.
	return close_path_vector.back();
}

void PathFindingManager::search_around_path(Path* const path) {
	// �ֺ� ��ǥ�� �˻��ϰ�, ���ǿ� ������ open_path�� �߰��Ѵ�.
	int x = path->x;
	int y = path->y;
	// left
	open_path(x + 1, y, 1, path);
	// right
	open_path(x - 1, y, 1, path);
	// up
	open_path(x, y + 1, 1, path);
	// down
	open_path(x, y - 1, 1, path);
	// up_right
	open_path(x + 1, y + 1, 1.414f, path);
	// down_right
	open_path(x + 1, y - 1, 1.414f, path);
	// up_left
	open_path(x - 1, y + 1, 1.414f, path);
	// up_left
	open_path(x - 1, y - 1, 1.414f, path);
}

void PathFindingManager::open_path(const int _x, const int _y, const int _cost, Path* const _parent) {
	// �� �� �Ǵ� close_path �̸� �߰����� �ʴ´�.
	int idx = _y * size_x + _x;
	
	if (is_out_bounds(_x, _y)) return;
	if (close_path_overlap(idx)) return;

	// *************** ���� ���� ������ �˻��ؾ��Ѵ�. ***************
	//if (map[ty][tx] == 1) continue;

	// path�� ��� opne_path�� ������ش�.
	// �� �̹� ��ϵ� path�� ����� �� ���ش�.
	Path* new_path = new Path(_x, _y, idx, _parent);
	new_path->consumption_cost = _parent->consumption_cost + _cost;
	new_path->expected_cost = new_path->manhattan_distance(end_path);
	
	int location = open_path_overlap(idx);
	if (location != -1) {
		update_path_value(_cost, location, new_path);
		return;
	}
	// �� ���濡 �����ϰų� ��ϵ��� �ʾҴٸ� open_path�� �߰� �Ѵ�.
	open_path_vector.push_back(new_path);
}

const bool PathFindingManager::close_path_overlap(const int _idx) const {
	for (Path* path : close_path_vector) {
		if (_idx == path->idx)
			return true;
	}
	return false;
}

const int PathFindingManager::open_path_overlap(const int _idx) const {
	int size = open_path_vector.size();
	int location = -1, i = 0;

	for (Path* path : open_path_vector) {
		if (_idx == path->idx) {
			location = i;
			break;
		}
		++i;
	}
	return location;
}

void PathFindingManager::update_path_value(const int _cost, const int i, Path* const _new_path) {
	// ������ ����� ��ο� �ű� ��θ� ���ؼ� cost�� ������ �����Ѵ�.
	if (_new_path->get_cost() < open_path_vector[i]->get_cost()) {
		delete open_path_vector[i];
		open_path_vector[i] = _new_path;

		/*open_path_vector[i]->consumption_cost = _new_path->consumption_cost;
		open_path_vector[i]->expected_cost = _new_path->expected_cost;
		open_path_vector[i]->parent = _new_path->parent;
		delete _new_path;*/
	}
}

//void PathFindingManager::open_path(const int _x, const int _y, const int _cost, Path* const _parent) {
//	int idx = _y * size_x + _x;
//	if (is_out_bounds(_x, _y)) return;
//	if (close_path_overlap(idx)) return;
//
//	Path* new_path = new Path(_x, _y, idx, _parent);
//	new_path->consumption_cost = _cost;
//	new_path->expected_cost = new_path->manhattan_distance(end_path);
//	int size = open_path_vector.size();
//
//	for (int i = 0; i < size; ++i) {
//		if (idx == open_path_vector[i]->idx) {
//			if (!update_path_value(_cost, i, new_path)) return;
//			//update_path_value(_cost, i, new_path);
//			return;
//		}
//	}
//	open_path_vector.push_back(new_path);
//}

//const bool update_path_value(const int _cost, const int i, Path* const _path) const;
//const bool PathFindingManager::update_path_value(const int _cost, const int i, Path* const _new_path) const {
//	// g ���� ���ؼ� �� ���ٸ� g ���� parent�� �����ϰ� true�� ��ȯ
//	float new_f = _new_path->consumption_cost + _cost + open_path_vector[i]->expected_cost;
//	if (new_f < open_path_vector[i]->get_cost()) {
//		open_path_vector[i]->consumption_cost = _new_path->consumption_cost + _cost;
//		open_path_vector[i]->parent = _new_path;
//		return true;
//	}
//	// �ƴ϶�� �Ҵ��� �����ϰ� flase�� ��ȯ�Ѵ�.
//	else {
//	delete _new_path;
//	return false;
//	}
//}