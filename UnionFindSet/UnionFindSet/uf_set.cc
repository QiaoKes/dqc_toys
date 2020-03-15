#include "uf_set.h"

uf_set::uf_set(std::size_t n)
{
	_curr_area = n;
	_parents = std::vector<int>(n + 1, 0);
	_ranks = std::vector<int>(n + 1, 0);
	for (std::size_t i = 0; i < n + 1; ++i)
		_parents[i] = i;
}

/*递归实现 简洁
int uf_set::find(int x)
{
	if (x != _parents[x]) {
		_parents[x] = find(_parents[x]);
	}
	return _parents[x];
}
*/

//迭代实现 更快更好 
int uf_set::find(int x)
{
	while (x != _parents[x]) {
		auto root = _parents[x];
		_parents[x] = _parents[root];
		x = root;
	}
	return _parents[x];
}

//合并两个节点 返回是否成功
bool uf_set::union_set(int x, int y)
{
	int x_root = find(x);
	int y_root = find(y);
	if (x_root == y_root) {
		return false;
	}
	if (_ranks[x_root] < _ranks[y_root]) {
		_parents[x_root] = y_root;
	}
	else if (_ranks[y_root] < _ranks[x_root]) {
		_parents[y_root] = x_root;
	}
	else if (_ranks[y_root] == _ranks[x_root]) {
		_parents[y_root] = x_root;
		++_ranks[x_root];
	}
	--_curr_area;
	return true;
}

//判断两个节点是否连接
bool uf_set::is_connected(int x, int y)
{
	return find(x) == find(y);
}

//连通分量
std::size_t uf_set::get_area_number() const
{
	return _curr_area;
}