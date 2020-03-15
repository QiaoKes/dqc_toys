#pragma once
#include <vector>

class uf_set {
public:
	uf_set(std::size_t);
	uf_set() = delete;	
	uf_set(const uf_set&) = delete;
	uf_set& operator=(const uf_set&) = delete;
	~uf_set() = default;

	bool union_set(int, int);
	int find(int);
	bool is_connected(int, int);
	std::size_t get_area_number() const;
	void clear() noexcept;
private:
	std::vector<int> _parents;
	std::vector<int> _ranks;
	int	_curr_area;
};
