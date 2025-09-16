#include <iostream>
#include <vector>
std::vector<int> vec{1,2,3};
using std::cbegin, std::cend;

template<typename C, typename V>
void findAndInsert(C& container,            //在容器中查找第一次
                   const V& targetVal,      //出现targetVal的位置，
                   const V& insertVal)      //然后在那插入insertVal
{
    using std::cbegin;
    using std::cend;

    auto it = std::find(cbegin(container),  //非成员函数cbegin
                        cend(container),    //非成员函数cend
                        targetVal);
    container.insert(it, insertVal);
}
//尽量先使用 cbegin cend 因为这是const的  cbegin cend等const_iterator 值得类似于 const int / const int*
void TestFunc()
{
    // auto pos = std::find(vec.);
}

int main()
{


    return 0;
}