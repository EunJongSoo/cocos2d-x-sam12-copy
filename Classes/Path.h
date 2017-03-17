#ifndef PATH_H_
#define PATH_H_

#include <math.h>

class Path {
public:
	Path() : parent(0) {}
	Path(int _x, int _y, Path* _parent = 0) 
		: x(_x), y(_y), index(_y * SIZE_X + _x), g(0), h(0), parent(_parent) {}
	~Path() {}

	float get_f() { return g + h; }
	float manhattan_distance(Path* _end_path) {
		float fx = fabs(x - _end_path->x);
		float fy = fabs(y - _end_path->y);
		return fx + fy;
	}
	int x;
	int y;
	int index;
	float g;
	float h;
	Path* parent;
};

#endif