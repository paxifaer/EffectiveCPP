#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <thread>
#include <functional>
#include <chrono>

enum class ThreadType{
  join,
  detach
};

class ThreadRAII{
public:
    ThreadRAII(std::thread&& t, ThreadType type)
        : t_(std::move(t)), type(type) {}

    std::thread& get(){ return t_; }

    ~ThreadRAII()
    {
        if(t_.joinable())
        {
           if(type == ThreadType::join) t_.join();
           else t_.detach();
        }
    }

private:
    std::thread t_;
    ThreadType type;
};

void TestFunc()
{
    ThreadRAII thread_rall(std::thread([]{
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "aaa" << std::endl;
    }), ThreadType::join);

    auto &t = thread_rall.get();
    auto handle = t.native_handle();

    // 设置调度参数（优先级）
    sched_param sch_params;
    sch_params.sched_priority = 20;  // 注意：1~99
    if(pthread_setschedparam(handle, SCHED_FIFO, &sch_params) != 0){
        std::cerr << "Failed to set thread priority. Need root?\n";
    }

    // 可选：立即等待线程完成
    t.join();  // 可去掉，RAII 析构会自动 join
}

int main()
{
    TestFunc();
    return 0;
}
