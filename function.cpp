#include <iostream>
#include <functional>
#include <future>
int testfunc(int a=10)
{
    std::cout<<"int type a is"<<a<<std::endl;
    return 1;
}


int void_test_func(int a)
{
    std::cout<<"void func"<<std::endl;
    return a;
}



void function1(std::function<void()> func1)
{
   func1();
}

void function2(std::function<int(int)> func1)
{
   std::cout<<func1(1)<<std::endl;
}


void future()
{
   std::packaged_task<int(int)> task(testfunc);
   std::future<int> fu = task.get_future();
//    task(1);
   std::thread(std::move(task), 1).detach();
   fu.get();
}

int main()
{
    // function1(void_test_func);
    // function2(testfunc);
    return 0;
}