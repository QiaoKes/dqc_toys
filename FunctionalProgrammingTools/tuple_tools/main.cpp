#include <iostream>
#include "extuple.h"
#include <numeric>
#include <string>
#include "exlambda.h"
#include <bitset>
using namespace std;
using namespace exfp;


int main()
{

    cout << (make_tuple(1,2) | [](int _, int __) { return _ + __; }
                             | [](int _) { return _ * 2; }
                             | [](int _) { return "result= " + std::to_string(_); }) << endl;

    auto gcd = Y(
        [](auto g, int a, int b)->int { return b == 0 ? a : g(b, a % b); }
    );

    cout << gcd(63, 105) << endl; // => 21

   
    auto t = make_tuple("heae", "dad", 1, 2);
    print_tuple(t); cout << endl;
    cout << head(t) << endl;
    cout << last(t) << endl;
    print_tuple(tail(t)); cout << endl;
    print_tuple(init(t)); cout << endl;

    auto fx = [](int a, int b)->int { return a + b; };
   // cout << fx(5) << endl;
    print_tuple(init(make_tuple("hel")));
    bitset<32>(2 ^ 3).count();
}

