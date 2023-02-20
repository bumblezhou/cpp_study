
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include<iostream>

using namespace std;

template<typename Container, typename Index> // works, but
// auto authAndAccess(Container& c, Index i) -> decltype(c[i]) // C++ 11
auto authAndAccess(Container& c, Index i)   // C++ 14
{
//  authenticateUser();
 return c[i];
}

int main()
{
    const int test_array[5] = {12, 324, 45, 56, 67};
    for(auto it : test_array) {
        cout << "it:" << it << endl;
    }
    auto x = authAndAccess(test_array, 2);
    cout << "x:" << x << endl;
    
    const std::string str_array[5] = {
        {"Hello"},
        {"World"},
        {"I am studying C++"},
        {"oh my gosh"},
        {"Everything is OK."}
    };
    for(auto str : str_array) {
        cout << "str:" << str << endl;
    }
    auto tmp = authAndAccess(str_array, 3);
    cout << "tmp:" << tmp << endl;
    return 0;
}
