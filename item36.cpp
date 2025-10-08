#include <iostream>
#include <type_traits>
#include <chrono>
#include <thread>
#include <future>
#include <utility>
#include <vector>

template<class F, class ... Args>
  decltype(auto) ReallyAsync(F &&f, Args&& ...args)
  {
      return std::async(std::launch::async, std::forward<F>(f), std::forward<Args>(args)...);
  } 


template<class F, class ... Args>
  decltype(auto) ReallyDerfer(F &&f, Args&& ...args)
  {
      return std::async(std::launch::deferred, std::forward<F>(f), std::forward<Args>(args)...);
  } 


void test_func(int a)
{
    std::cout<<" test func "<< a <<"this thread id is "<< std::this_thread::get_id() <<std::endl;   

}

void test_func2(int a)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout<<" test func2 "<< a <<std::endl;  
}

int main()
{


    auto fun1 = ReallyAsync(test_func2, 2);
    auto fun2 = ReallyAsync(test_func, 3);
    std::vector<std::future<void>> vec;
    fun2.get();
    fun1.get();
    for(int i=0;i<100;i++)
    {
        vec.emplace_back(ReallyAsync(test_func, i));
    }

    for(auto& ele:vec)
    {
        ele.get();
    }

    auto fun3 = ReallyDerfer(test_func2, 2);
    
    fun3.get();
    /*
    1.多线程开发时候，以task为导向，而不是以线程为导向。
    2.std::launch::async 将任务放一新线程(不确定)当你使用 std::async(std::launch::async, ...) 时，标准保证任务会在独立线程中异步执行，
        但 并不保证它一定是一个“全新的”操作系统线程。
        换句话说：
        一定不是当前线程（main 线程）；
        一定是“并发执行”的；
        是否复用线程由实现（标准库）决定。
        但是基本上是该进程的新线程。
    3. std::launch::derferred 只有在调用 ->wait()或者 get时候新线程才会执行该任务，同时会阻塞调用线程
    */
    while(1)
    {

    }
    return 0;
}