#include <iostream>
#include <type_traits>
#include <utility>

template<typename T>
void f(T* param) {
    if (std::is_same_v<T, int>) {
        std::cout << "T is int, param is int*\n";
    } else if (std::is_same_v<T, const int>) {
        std::cout << "T is const int, param is const int*\n";
    }
}

template<typename T>
void f2(T& param)
{
    
}

template<typename T>
void f3(T param)
{
    if(std::is_same<T,const char* const>::value)
    {
        std::cout << "const char* const\n";
    }
    else if(std::is_same_v<T,const char* >)
    {
        std::cout << "const char*\n";
    }
    else if(std::is_same_v<T, char* >)
    {
        std::cout << " char*\n";
    }
}               //仍然以传值的方式处理param

const char* const ptr =         //ptr是一个常量指针，指向常量对象 
    "Fun with pointers";

template<class T>
auto&& f4(T &&para)
{
     
    int x=3;
    return (x);

}

template<class T>
decltype(auto) f5(T &&para)
{
     
    int x=3;
    return std::forward<T>((x));

}

void test_decltype()
{
     if(std::is_same_v<decltype(f4(4)),int&>)
     {
        std::cout<<"is int&"<<std::endl;
     }
     else if(std::is_same_v<decltype(f4(4)),int>)
     {
        std::cout<<"is int"<<std::endl;
     }



     if(std::is_same_v<decltype(f5<int>(4)),int&>)
     {
        std::cout<<"is int&"<<std::endl;
     }
     else if(std::is_same_v<decltype(f5<int>(4)),int>)
     {
        std::cout<<"is int"<<std::endl;
     }
     std::cout<<"type is "<<typeid(f5<int>(4)).name()<<std::endl;
    //  }     else if(std::is_same_v<decltype(f5<int>(4)),int&&>)
    //  {
    //     std::cout<<"is int&& x is"<<f5<int>(4)<<std::endl;//引发悬垂引用
    //  }
}

void process(int& x)  { std::cout << "左值: " << x << std::endl; }
void process(int&& x) { std::cout << "右值: " << x << std::endl; }

// 中间转发函数
template<typename T>
void relay(T&& arg) {
    process(std::forward<T>(arg)); // 完美转发
}

void test_forward()
{


    int x = 10;
    relay(x);       // 输出：左值: 10
    relay(20);      // 输出：右值: 20
    relay(std::move(x)); // 输出：右值: 10

}
int main() {
    int x = 27;
    const int *px = &x;

    // f(&x); // 输出：T is int, param is int*
    // f(px); // 输出：T is const int, param is const int*
    // int x=3;
    // f2(x);
    // f2(std::move(x));
    
    const char* const pa = "aaa";

    f3(pa);
    test_decltype();
    test_forward();
    return 0;
}