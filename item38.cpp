#include <iostream>
#include <type_traits>
#include <future>
#include <memory>
#include <thread>
#include <functional>

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


void test_promise1(std::promise<int> pse)
{
    int a = 10;
    pse.set_value(a);
}

void test_packaged_task(int a)
{
    std::cout<<" a is " << a <<std::endl;
}

int test_package_task2(int b)
{
  return 1;
}

void test2()
{
    std::promise<int> pro;
    auto fu = pro.get_future();
    std::thread(test_promise1, std::move(pro)).detach();
    std::cout<<" promise get value "<< fu.get()<<std::endl;

    std::packaged_task<void(int)> task{test_packaged_task};
    auto fu2 = task.get_future();
    std::thread(std::move(test_packaged_task), 100).detach();
    // fu2.get();

    std::packaged_task<int(int)> task3{test_package_task2};
    auto fu3 = task3.get_future();
    std::thread(std::move(task3), 100).detach();
    auto share1 = fu3.share();
    auto share1_1 = share1;
    auto share1_2 = share1;
    std::cout<<" share 1 is "<<share1_1.get()<<std::endl;
    std::cout<<" share 2 is "<<share1_2.get()<<std::endl;
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
    test2();
    return 0;
}