// 🚦 一、std::atomic：保证线程间操作原子性

// 用于多线程共享数据时，避免数据竞争（data race）。

// 所有读写、递增、递减、读改写（RMW）操作都是 不可分割的原子操作。

// 保证其他线程看到的值始终是一致的。

// 默认具有 顺序一致性（sequential consistency），避免编译器和 CPU 重排。

// 二、volatile：防止访问被优化掉

// 告诉编译器：每次读写都必须真的发生。

// 典型用途：访问 特殊硬件寄存器、内存映射I/O、跨进程共享内存 等。

// 不保证原子性，也不保证线程安全。

// - `std::atomic`用于在不使用互斥锁情况下，来使变量被多个线程访问的情况。是用来编写并发程序的一个工具。
// - `volatile`用在读取和写入不应被优化掉的内存上。是用来处理特殊内存的一个工具。
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <vector>

std::condition_variable cv_;
std::mutex mtx;
bool can_get = false;
int a=0;

void test()
{
    std::unique_lock<std::mutex> lk{mtx};
    cv_.wait(lk, []{
        return can_get;
    });
    a++;
    cv_.notify_all();
}



int main()
{
    std::vector<std::thread> pool;
    for(int i=0;i<100;i++)
    {
        pool.emplace_back(test);
    }

    {
        can_get = true;
        std::unique_lock<std::mutex> lk(mtx);
    }
    cv_.notify_one();

    for(auto & t:pool)
    {
        t.join();
    }


    std::cout<<"  end it "<<a<<std::endl;
    return 0;
}