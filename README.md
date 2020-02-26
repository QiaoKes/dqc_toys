# dqc_toys
一些玩具或者实验性的功能
* tuple扩展功能 c++14
* lambda函数扩展功能  c++17
  
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
    //很coooool的功能, 返回一个匿名的lambda递归函数
    auto gcd = Y(
        [](auto g, int a, int b)->int { return b == 0 ? a : g(b, a % b); }
    );
    cout << gcd(63, 105) << endl; // => 21
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
