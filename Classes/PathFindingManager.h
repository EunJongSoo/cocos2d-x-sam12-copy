#ifndef PATH_FINDING_H_
#define PATH_FINDING_H_

#include <vector>

using namespace std;

class Path;

class PathFindingManager {
public:
	struct vec2 {
		vec2(const int _x, const int _y) : x(_x), y(_y) {}
		unsigned int x;
		unsigned int y;
	};
	PathFindingManager();
	PathFindingManager(const int _size_x, const int _size_y, const int _size_cell);
	~PathFindingManager();
	void finding_path(const float _str_x, const float _str_y,
		const float _end_x, const float _end_y);
	void goal_path_clear();
	vector<vec2*> goal_path;
private:
	
	enum Direction {
		up, down, right, left,
		upper_left, lower_right, lower_left, upper_right, dir_count
	};
	const unsigned int size_x;
	const unsigned int size_y;
	const float size_cell;

	void init_path();
	void path_vector_clear(vector<Path*>& _vector);
	void finding_process();
	Path* search_next_path();
	void search_around_path(Path* const _path);
	void open_path(const int _x, const int _y, const int _cost, Path* const _parent);
	inline const bool is_out_bounds(const float _x, const float _y) const;
	const bool close_path_overlap(const int _idx) const;
	const int open_path_overlap(const int _idx) const;
	void update_path_value(const int _cost, const int i, Path* const _path);
	const bool is_goal(const int idx) const;
	void record_path(const Path* const _path);

	Path* start_path;
	Path* end_path;
	vector<Path*> open_path_vector;
	vector<Path*> close_path_vector;
};

inline const bool PathFindingManager::is_out_bounds(const float x, const float y) const {
	return (x < 0 || x >= size_x || y < 0 || y >= size_y);
}

#endif