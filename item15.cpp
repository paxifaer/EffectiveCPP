#include <iostream>

constexpr int square(int x) {
    return x * x;
}
/*
constexpr 必须返回值，否则无法在编译期计算。类的构造函数除外
*/ 

int get()
{
    int a;
    //a = get()...
    return a;
}

constexpr int func() {
    int a = get();  // 如果 get() 不是 constexpr 函数，编译期无法计算
    constexpr int b = 0;
    return b;
}
// 只要有任何在运行时计算的值，func() 就无法在编译期计算。

int func_(int a) { return a; }
constexpr int func2() {
    return func_(5);  // 编译期可计算，因为 func(5) 在编译期可以求得
}

int main()
{
constexpr int a = 3;
// a = 5;  // 错误，`a` 是 `constexpr`，不能修改
/*
总结：

constexpr 必须返回值，否则无法在编译期计算。

任何依赖于运行时值的计算，都会使得 constexpr 函数不能在编译期计算。

对于 constexpr 函数，它能够在编译期计算时，使用常量值作为参数就可以让返回值在编译期计算。

constexpr 对象与 const 相似，它们的值在声明时就已经确定，且不可修改。
*/ 
    return 0;
}