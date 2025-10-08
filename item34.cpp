// ⚙️ 性能与优化差异
// lambda 调用目标函数是 直接调用 → 编译器可内联优化；
// std::bind 内部存储 函数指针 → 调用是 间接调用，通常无法内联。
// 👉 因此 lambda 生成的代码通常 更快、更小、更易优化。
/*
🎯 特殊情况下 std::bind 才有用（仅限 C++11）

只有两个特例能让 std::bind 在 C++11 下保留价值：

模拟“移动捕获”（因为 C++11 的 lambda 不能移动捕获对象）：

auto ptr = std::make_unique<Widget>();
auto f = std::bind([](std::unique_ptr<Widget>& p){ p->test(); },
                   std::move(ptr));


绑定多态函数对象（template call operator）：

class PolyWidget {
public:
    template<typename T> void operator()(const T& param);
};

PolyWidget pw;
auto bound = std::bind(pw, _1);  // bind 支持完美转发
bound(42);
bound("text");


在 C++14+，lambda 支持 auto 参数后，可以更好地实现：

auto bound = [pw](const auto& param) { pw(param); };
*/
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

class Wiget
{
public:
    Wiget() {}
    void test(int a)
    {
        std::cout << "test " <<a<< std::endl;
    }
    void test2()
    {
        auto func = std::bind(&Wiget::test, this, std::placeholders::_1);
        func(1);

        auto func2 = [this](int a)
        {
           this->test(a);
        };

        auto func3 = std::bind(&Wiget::test, this, std::placeholders::_1);
        int a=3;
        func3(a);

        auto func4 = [this](int &a)
        {
           this->test(a);
        };

        auto func5 = std::bind(&Wiget::test, this, std::ref(a));
        func5();
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
    Wiget w;
    w.test2();


    return 0;
}
