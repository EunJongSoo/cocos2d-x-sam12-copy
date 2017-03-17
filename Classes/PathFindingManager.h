#ifndef PATH_FINDING_H_
#define PATH_FINDING_H_

#define SIZE_X 96
#define SIZE_Y 64
#define SIZE_CELL 10.0f

#include <vector>
#include "Path.h"
#include "cocos2d.h"

using namespace std;

class PathFindingManager {
public:
	PathFindingManager();
	~PathFindingManager();
	void finding_path(const cocos2d::Point& _start_point, const cocos2d::Point& _end_point);
	void goal_path_back_erase();
	vector<cocos2d::Vec2*> goal_path;

private:
	enum Direction {
		up, down, right, left,
		upper_left, lower_right, lower_left, upper_right, dir_count
	};
	struct path_value {
		path_value() : x(0), y(0), cost(1.0f) {}
		path_value(int dir) : x(0), y(0), cost(1.0f) {
			set_value(dir);
		}
		void set_value(int dir) {
			switch (dir) {
			case Direction::up: x = 0, y = 1; break;
			case Direction::down: x = 0, y = -1; break;
			case Direction::left: x = -1, y = 0; break;
			case Direction::right: x = 1, y = 0; break;
			case Direction::upper_left: x = -1, y = 1, cost = 1.414f; break;
			case Direction::upper_right: x = 1, y = 1, cost = 1.414f; break;
			case Direction::lower_left: x = -1, y = -1, cost = 1.414f; break;
			case Direction::lower_right: x = 1, y = -1, cost = 1.414f; break;
			}
		}
		int x;
		int y;
		float cost;
	};

	void init_path();
	bool finding_process();
	Path* search_next_path();
	bool is_destination_arrival(Path* path);
	void search_around_path(Path* _parent);
	bool is_out_bounds(float x, float y);
	bool is_close_path(int _index);
	void path_open(int _tx, int _ty, int _cost, Path* _parent);
	bool update_path_value(Path* _path, int _cost, int i);

	Path* start_path;
	Path* end_path;
	vector<Path*> open_path;
	vector<Path*> close_path;
};


#endif