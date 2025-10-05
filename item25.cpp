// “RVO 的情况就是：函数返回局部对象或临时对象（类型匹配，没加 std::move）。
// 除了这种情况，其余该 std::move 的地方都可以用。”
/*返回右值引用或通用引用形参
✅ 必须用 std::move 或 std::forward
否则强制拷贝*/

#include <iostream>
#include <type_traits>


int main()
{
    return 0;
}