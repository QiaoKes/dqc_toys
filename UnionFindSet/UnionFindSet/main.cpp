#include <iostream>
#include <vector>
#include "uf_set.h"
using namespace std;

int findCircleNum(vector<vector<int>>& M) {
    int n = M.size();
    uf_set s(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (M[i][j] == 1) s.union_set(i, j);
        }
    }
    return s.get_area_number();
}

int main()
{
    vector<vector<int>> input = { {1, 1, 0},{1, 1, 0}, { 0, 0, 1 }};
    cout << findCircleNum(input);
}
