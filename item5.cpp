#include <iostream>

using namespace std;
class Widget {};

Widget& func() {
    static Widget w;
    return w;
}

int main()
{
    auto w1 = func();   // #1
    auto& w2 = func();  // #2


    return 0;
}
/*
auto默认去掉const和引用，创建新对象
auto&保持引用
*/ 