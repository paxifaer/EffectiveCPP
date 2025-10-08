#include <iostream>
#include <memory>
#include <vector>
#include <functional>

class Wiget
{
public:
    Wiget() {}
    void test()
    {
        std::cout << "test " << std::endl;
    }
};

void func(int &x)
{
    std::cout << " lvalue test " << x << std::endl;
}

void func(int &&x)
{
    std::cout << " rvalue test " << x << std::endl;
}

int main()
{
    auto func1 = [](auto para) { // para 左值
        //  std::cout<<"test func1 "<<std::endl;
        func(para);
    };

    auto func2 = [](auto &&para)
    {
        func(std::forward<decltype(para)>(para));
    };

    auto func3 = [](auto &&...para)
    {
        func(std::forward<decltype(para)>(para)...);
    };
    int a = 1;
    func1(1);
    func1(a);
    int a1 = 1;
    func2(2);
    func2(a1);

    int a2 = 1;
    func3(2);
    func3(a1);
    return 0;
}