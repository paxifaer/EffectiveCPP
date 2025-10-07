#include <iostream>
#include <functional>
#include <vector>
//  默认的按引用捕获可能会导致悬空引用。
//  默认的按值捕获对于悬空指针很敏感（尤其是`this`指针），并且它会误导人产生*lambda*是独立的想法。

int computeSomeValue1()
{
   return 1;
}

int computeSomeValue2()
{
   return 1;
}

int computeDivisor(int a, int b)
{

}

std::vector<std::function<bool(int)>> filters;

void addDivisorFilter()
{
    static auto calc1 = computeSomeValue1();    //现在是static
    static auto calc2 = computeSomeValue2();    //现在是static
    static auto divisor =                       //现在是static
    computeDivisor(calc1, calc2);

    filters.emplace_back(
        [=](int value)                          //什么也没捕获到！
        { return value % divisor == 0; }        //引用上面的static
    );

    ++divisor;                                  //调整divisor
}

int main()
{
    return 0;
}