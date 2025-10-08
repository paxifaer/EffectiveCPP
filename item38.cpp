#include <iostream>
#include <type_traits>
#include <future>
#include <memory>
#include <thread>

class Widget{
  public:
     
    Widget(std::shared_future<int> fu) : fu_(fu)
    {
    }

    void print()
    {
        std::cout<<" the result is "<<fu_.get()<<std::endl;
    }
  private:
    std::shared_future<int> fu_;
};

int test_func()
{
    return 9;
}

int main()
{
    std::packaged_task<int()> pk(test_func);

    auto fu = pk.get_future();
    auto s_f = fu.share();
    
    Widget a1(s_f);
    Widget a2(s_f);

    std::thread(std::move(pk)).detach();
    a1.print(), a2.print();

    return 0;
}