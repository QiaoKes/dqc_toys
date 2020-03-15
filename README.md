# dqc_toys
一些玩具或者实验性的功能
* tuple扩展功能 c++14
* lambda函数扩展功能  c++17
* 并查集 c++11
  
###FunctionalProgrammingTools###c++函数式编程扩展库  
**1.tuple扩展**


```C++
#include <tuple>
#include "extuple.h"
using namespace std;
using namespace exfp;

int main()
{
    auto t = make_tuple("head", "dad", 1, 2);
    
    //返回tuple的长度
    cout << tuple_length(t);
    // => 4
    
    //输出tuple序列
    print_tuple(t); cout << endl;
    // => (head, dad, 1, 2)
    
    //返回tuple头元素
    cout << head(t) << endl;
    // => head
    
    //返回tuple尾元素
    cout << last(t) << endl;
    // => 2
    
    //返回除头外的tuple
    print_tuple(tail(t)); cout << endl;
    // => (dad, 1, 2)
    
    //返回除尾外的tuple
    print_tuple(init(t)); cout << endl;
    // => (head, dad, 1)
    
}
```  

**2.lambda扩展**
```C++
#include <iostream>
#include "exlambda.h"
using namespace std;
using namespace exfp;

int main()
{
    //Y组合子 很coooool的功能, 返回一个匿名的lambda递归函数
    auto gcd = Y(
        [](auto g, int a, int b)->int { return b == 0 ? a : g(b, a % b); }
    );
    cout << gcd(63, 105) << endl; 
    // => 21
    
    //像管道一样传输数据  eg: (参数包) | (函数)
    //单个参数如下
    cout << (2 | [](int _) { return _ + 3; }
               | [](int _) { return _ * 2; }
               | [](int _) { return "result= " + std::to_string(_); }) << endl;
    // => result= 10
    
    //多个参数用tuple包装起来即可        
    cout << (make_tuple(1,2) | [](int _, int __) { return _ + __; }
                             | [](int _) { return _ * 2; }
                             | [](int _) { return "result= " + std::to_string(_); }) << endl;
    // => result= 6

}
```
###UnionFindSet###并查集  
  
**特性:**  
```
1.不支持拷贝构造  
2.不支持拷贝复制  
3.不支持无参构造  
```
**功能:**  
```
1.bool union_set(int x, int y)   
  合并两个节点，返回是否并成功。   
2.int find(int x)  
  返回x的祖先。  
3.bool is_connected(int x, int y)  
  返回x, y是否连通。
4.std::size_t get_area_number();  
  返回当前集合的个数。  
5.clear()
  清空当前uf_set。  
```  
**样例:**  
___1.leetcode 684.[冗余连接](https://leetcode-cn.com/problems/redundant-connection/)___    
  ```C++
#include <uf_set.h>
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        uf_set s(edges.size());
        for(const auto& edge : edges) {
            if (s.union_set(edge[0], edge[1]) == false)
                return {edge[0], edge[1]};
        }
        return { };
    }
};
  ```  
 ___2.leetcode 547.[朋友圈](https://leetcode-cn.com/problems/friend-circles/)___    
  ```C++
#include <uf_set.h>
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        uf_set s(n);
        for(int i = 0; i < n; ++i) {
            for(int j = i+1; j < n; ++j) {
                if (M[i][j] == 1) s.union_set(i, j);
            }
        }
        //返回现有集合数量
        return s.get_area_number();
    }
};
  ```  
  ___3.leetcode 200.[岛屿数量](https://leetcode-cn.com/problems/number-of-islands/)___    
  ```C++
#include <uf_set.h>
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        auto n = grid.size();
        //判断是否为空
        if(n == 0) return 0;
        auto m = grid[0].size();
        //做一个海洋节点
        int sea_index = n*m;
        uf_set s(sea_index+1);
        //将二维数组投影为一维
        auto get_index = [&m](int i, int j)->int {
            return i * m + j;
        };
        //两个移动方向 向下 向右
        vector<vector<int>> directions = {{1,0}, {0,1}};
        for(size_t i = 0; i < n; ++i) {
            for(size_t j = 0; j < m; ++j) {
                //若是海洋 与海洋节点相连
                if (grid[i][j] == '0')
                    s.union_set(get_index(i, j), sea_index);
                //若为大陆 判断其余两个方向是否相连
                if (grid[i][j] == '1')
                    //遍历所有移动方向
                    for(auto& dire : directions) {
                        auto next_x = i + dire[0];
                        auto next_y = j + dire[1];
                        if (next_x < n && next_y < m && grid[next_x][next_y] == '1')
                            s.union_set(get_index(i, j), get_index(next_x, next_y));
                    }
            }
        }
        //返回现存集合数量 去掉海洋
        return s.get_area_number() - 1; 
    }
};
  ```
