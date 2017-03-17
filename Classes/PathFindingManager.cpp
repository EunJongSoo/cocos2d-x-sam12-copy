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

	// 길 찾는 중
	while (!finding_process());
	// 길 찾기 성공하면 ~
}

bool PathFindingManager::finding_process() {
	Path* path = search_next_path();
	// 다음 path가 목적지 인지 검사합니다.
	if (is_destination_arrival(path)) {
		return true;
	}
	// 도착 못했을시 주변 검사
	search_around_path(path);
	return false;
}

Path* PathFindingManager::search_next_path() {
	// open_path가 비었으면 nullptr을 반환합니다.
	if (open_path.empty()) return nullptr;

	// 임시로 f에 큰 값을 주고 open_path에 있는 값 중에서 가장 작은 값을 찾습니다.
	float best_f = 9999999.0f;
	int location = 0;
	for (int i = 0; i < open_path.size(); ++i) {
		if (open_path[i]->get_f() < best_f) {
			best_f = open_path[i]->get_f();
			location = i;
		}
	}
	// 가장 f값이 작은 path를 close_path에 등록하고, open_path에서 빼줍니다.
	close_path.push_back(open_path[location]);
	open_path.erase(open_path.begin() + location);

	// 마지막에 등록된 값을 반환 합니다.
	return close_path.back();
}

bool PathFindingManager::is_destination_arrival(Path* path) {
	if (end_path->index == path->index) {
		end_path->parent = path->parent;
		Path* get_path;
		// 목적지 이면 도착지부터 시작점 까지 경로를 저장합니다.
		for (get_path = end_path; get_path != NULL; get_path = get_path->parent) {
			goal_path.push_back(new Vec2(get_path->x * SIZE_CELL, get_path->y * SIZE_CELL));
		}
		return true;
	}
	return false;
}

void PathFindingManager::search_around_path(Path* path) {
	// 주변 좌표를 검색하고, 조건에 맞으면 open_path에 추가한다.
	path_value tmp_value;
	int tx = 0, ty = 0, index = 0;
	for (int i = 0; i < Direction::dir_count; ++i) {
		tmp_value.set_value(i);
		tx = path->x + tmp_value.x;
		ty = path->y + tmp_value.y;
		index = ty * SIZE_X + tx;
		// 맵 밖 또는 close_path 이면 추가하지 않는다.
		if (is_out_bounds(tx, ty) || is_close_path(index)) continue;
		

		// *************** 갈수 없는 지역도 검사해야한다. ***************
		//if (map[ty][tx] == 1) continue;


		path_open(tx, ty, tmp_value.cost, path);
	}
}


bool PathFindingManager::is_out_bounds(float x, float y) {
	// 좌표값이 맵 밖이면 ture, 안쪽이면 false를 반환한다.
	if (x < 0 || x >= SIZE_X || y < 0 || y >= SIZE_Y) {
		return true;
	}
	return false;
}


bool PathFindingManager::is_close_path(int _index) {
	// close_path에 등록되었으면 true, 아니면 false를 반환한다.
	for (int i = 0; i < close_path.size(); ++i) {
		if (_index == close_path[i]->index) {
			return true;
		}
	}
	return false;
}


void PathFindingManager::path_open(int _tx, int _ty, int _cost, Path* _parent) {
	// path를 등록 opne_path에 등록해준다.
	// 단 이미 등록된 path는 비용을 비교 해준다.
	Path* new_path = new Path(_tx, _ty, _parent);
	new_path->g = _cost;
	new_path->h = new_path->manhattan_distance(end_path);
	for (int i = 0; i < open_path.size(); ++i) {
		if (new_path->index == open_path[i]->index) {
			// path_value 값 변경이 실패하면 open_path에 추가하지 않고 함수를 중단한다.
			if (!update_path_value(new_path, _cost, i)) return;
		}
	}
	// 값 변경에 성공하거나 등록되지 않았다면 open_path에 추가 한다.
	open_path.push_back(new_path);
}


bool PathFindingManager::update_path_value(Path* _path, int _cost, int i) {
	// g 값을 비교해서 더 낮다면 g 값과 parent를 변경하고 true를 반환
	float new_f = _path->g + _cost + open_path[i]->h;
	if (new_f < open_path[i]->get_f()) {
		open_path[i]->g = _path->g + _cost;
		open_path[i]->parent = _path;
		return true;
	}
	// 아니라면 할당을 해제하고 flase를 반환한다.
	else {
		delete _path;
		return false;
	}
}