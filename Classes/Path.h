#ifndef PATH_H_
#define PATH_H_

#include <math.h>

class Path {
public:
	Path() : parent(nullptr) {}
	Path(int _x, int _y, int _idx, Path* _parent = nullptr)
		: x(_x), y(_y), idx(_idx), consumption_cost(0.0f), expected_cost(0.0f), parent(_parent) {}
	~Path() {}

	Path* get_parent() const { return parent; }
	void set_parent(Path* _parent) { parent = _parent; }
	inline const float get_cost() const { return consumption_cost + expected_cost; }
	const float manhattan_distance(Path* _end_path) const {
		float fx = fabs(x - _end_path->x);
		float fy = fabs(y - _end_path->y);
		return fx + fy;
	}
	
	int x;
	int y;
	unsigned int idx;
	float consumption_cost;
	float expected_cost;

private:
	Path* parent;
};

#endif