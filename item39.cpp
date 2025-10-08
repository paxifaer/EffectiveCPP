#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <chrono>
// #include <conditional>

void test_promise(std::promise<int> p)
{
    int a = 4;
    p.set_value(a);
}

std::condition_variable cv_;
bool flag = false;
std::mutex mtx;

void detect()
{
    static int dec = 0;
    while (true)
    {
        std::unique_lock<std::mutex> lk(mtx);
        cv_.wait(lk, []()
                 { return flag; });
        std::cout << " dec is " << dec++ << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds(200));
        flag = false;
    }
}

void react()
{
    while (true)
    {
        {        
            std::lock_guard<std::mutex> lk(mtx);
            flag = true;
            // std::this_thread::sleep_for(std::chrono::milliseconds(200));  绝不能在这里sleep
            cv_.notify_one();
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main()
{
    std::promise<int> p;
    auto fu = p.get_future();
    std::thread t(test_promise, std::move(p));
    t.join();
    std::cout << " promise is " << fu.get() << std::endl;

    std::thread(detect).detach();
    // std::thread(react).detach();
    std::thread(react).detach();
    flag = true;
    while (true)
    {
        /* code */
    }
    
    return 0;
}