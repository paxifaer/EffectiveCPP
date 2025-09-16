🔹 1. C 里的“异常处理”

严格来说，C 语言没有内建的异常机制。
在 C 里常见的几种“异常处理”方式：

返回值检查

最经典：函数失败时返回 -1 或 NULL，成功时返回正常值。

例子：

FILE* f = fopen("data.txt", "r");
if (!f) {
    // 错误处理
    perror("打开文件失败");
    return -1;
}


errno 全局变量

C 标准库里定义了一个全局变量 errno，函数失败时会设置它。

例子：

#include <errno.h>
#include <string.h>
if (f == NULL) {
    printf("错误: %s\n", strerror(errno));
}


setjmp/longjmp（跳转）

C 里比较“像异常”的机制，来自 <setjmp.h>。

setjmp 保存上下文，longjmp 跳转回去。

缺点：破坏控制流，容易出 bug，几乎没人推荐。

👉 所以：C 没有“throw/catch”，只能用返回值/errno或长跳转来模拟。

🔹 2. C++ 异常处理

C++ 提供了完整的异常机制：throw + try + catch。

2.1 抛出异常 throw

用 throw 抛出一个对象（通常是 std::exception 或其子类）。

例子：

void divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("除零错误");
    }
    std::cout << a / b << std::endl;
}

2.2 捕获异常 try + catch

用 try 包裹代码，用 catch 捕获异常。

例子：

try {
    divide(10, 0);
} catch (const std::runtime_error& e) {
    std::cerr << "捕获到错误: " << e.what() << std::endl;
} catch (...) {  // catch-all
    std::cerr << "捕获到未知错误" << std::endl;
}

2.3 terminate 触发情况

如果异常没有被捕获，程序会调用 std::terminate，默认行为是直接结束程序。
会触发 terminate 的几种情况：

抛出了异常但没有任何 catch 捕获它。

在 noexcept 函数里异常向外逃逸。

析构函数在栈展开期间再次抛异常（双重异常）。

🔹 3. 用法要点总结

异常类型

推荐抛出标准异常（<stdexcept>）或自定义继承自 std::exception 的类。

标准异常例子：

std::runtime_error（运行时错误）

std::invalid_argument（无效参数）

std::out_of_range（越界）

std::bad_alloc（内存分配失败）

异常捕获方式

一般写 catch (const std::exception& e)，这样能捕获大多数异常并调用 e.what()。

catch (...) 可以兜底，但不知道错误细节。

栈展开（stack unwinding）

当异常抛出时，程序会从抛出点往上找 catch，沿途调用已构造对象的析构函数，保证资源释放。

这就是 C++ RAII 能很好配合异常的原因。

🔹 4. C vs C++ 对比总结表
特性	C	C++
内建异常机制	❌ 无	✅ 有（throw/try/catch）
常用方式	错误码、errno、setjmp/longjmp	抛异常、捕获异常
资源释放	手动清理	RAII + 栈展开自动调用析构
未处理错误	程序继续（可能 UB）	调用 std::terminate 结束程序
常见用法	if (ret < 0) {}	try { ... } catch (...) {}
🔹 5. 经典用法
C 经典用法
FILE* f = fopen("test.txt", "r");
if (!f) {
    perror("打开文件失败");
    return -1;
}

C++ 经典用法
try {
    std::vector<int> v(1000000000000); // 可能抛 bad_alloc
} catch (const std::bad_alloc& e) {
    std::cerr << "内存不足: " << e.what() << std::endl;
}


✅ 这样你就有一个完整图景了：

C：没有异常，用错误码/errno 或 setjmp/longjmp。

C++：throw + try + catch，自动栈展开，未捕获会 terminate。

关键点：C++ 的 noexcept 语义会影响 terminate 触发条件。

要不要我帮你画一个**“异常传播流程图（throw → catch → terminate）”**？这样你一看图就能记住整个流程。

您说：
这里还有runtimerror啊，意思是数组越界也能报异常？一般的数组和stl也能这么做吗
ChatGPT 说：

好问题 👌 你抓到了 C++ 异常处理里一个容易误解的地方。
我们要区分：

🔹 1. 原生数组（C-style array）
int arr[3] = {1, 2, 3};
int x = arr[10]; // 越界


👉 这是 未定义行为 (UB)，不会抛异常。
C++ 语言层面规定，对原生数组越界访问就是 UB —— 编译器不会帮你抛 std::runtime_error，可能崩溃、可能打印垃圾、甚至什么事也没发生。

🔹 2. STL 容器的两种访问方式

STL 容器（如 std::vector、std::string）有 两套访问接口：

(1) operator[]（下标运算符）
std::vector<int> v{1, 2, 3};
int x = v[10];  // 未定义行为 (UB)，不会抛异常


和原生数组一样，不会检查越界。

出于效率考虑，标准规定不做边界检查。

(2) .at() 成员函数
std::vector<int> v{1, 2, 3};
try {
    int x = v.at(10);   // 会抛 std::out_of_range
} catch (const std::out_of_range& e) {
    std::cerr << "捕获异常: " << e.what() << std::endl;
}


.at() 会检查边界，越界时抛 std::out_of_range（继承自 std::logic_error → std::exception）。

这是 标准库内置的安全访问方式。

🔹 3. 常见标准异常

C++ 标准库提供了一些常见的异常类（在 <stdexcept> 里）：

std::runtime_error：运行时错误（通常程序状态导致的，比如 I/O 错误）。

std::logic_error：逻辑错误（程序设计不当，比如参数不合法）。

std::invalid_argument

std::out_of_range

std::bad_alloc：内存分配失败。

std::overflow_error / std::underflow_error：数值溢出相关。

👉 注意：数组越界检查不是自动的，除非你用 .at()，否则不会抛 std::out_of_range。

🔹 4. 总结一句话

原生数组：越界 = 未定义行为，不抛异常。

STL 容器：

operator[] → 不检查，不抛异常。

.at() → 检查，越界抛 std::out_of_range。

要不要我给你画一个 “数组/容器越界时行为对比表”？这样能一眼看清楚：原生数组 vs STL [] vs STL