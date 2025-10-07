#include <iostream>
#include <memory>
#include <vector>
#include <functional>

class Wiget{
  public:
    Wiget(){}
    void test()
    {
        std::cout<<"test "<<std::endl;
    }
};

int main()
{
    auto pw = std::make_unique<Wiget>();
    auto func = [pw = std::move(pw)](){
        pw->test();
    };

    func();
    auto pw2 = std::make_unique<Wiget>();
    auto func2 = std::bind([](std::unique_ptr<Wiget> pw){}
                 , std::move(pw2));
                 
    std::vector<double> data = {1.0, 2.0, 3.0};
    auto func3 = std::bind(
        [](const std::vector<double>& d) {
            /* 使用 d */
        },
        std::move(data) // 移动进 bind 对象
    );

    return 0;
}