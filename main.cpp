#include <iostream>
#include <type_traits>
#include <utility>
#include <memory>
#include<stdio.h>
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
    return x;
}

template<class T>
decltype(auto) f5(T &&para)
{
     
    int x=3;
    return std::forward<T>((x));

}

template<class T>
decltype(auto) f6()
{
    int x=3;
    return x;
}

template<class T>
decltype(auto) f6_2()//decltype((value)) (value)被识别为一个表达式
{
    int x=3;
    return (x);
}

void test_decltype()
{
     if(std::is_same_v<decltype(f4(4)),int&>)
     {
        std::cout<<"f4 is int&"<<std::endl;
     }
     else if(std::is_same_v<decltype(f4(4)),int>)
     {
        std::cout<<"f4 is int"<<std::endl;
     }



     if(std::is_same_v<decltype(f5<int>(4)),int&>)
     {
        std::cout<<"f5 is int&"<<std::endl;
     }
     else if(std::is_same_v<decltype(f5<int>(4)),int>)
     {
        std::cout<<"f5 is int"<<std::endl;
     }    else if(std::is_same_v<decltype(f5<int>(4)),int&&>)
     {
        std::cout<<"f5 is int&&"<<std::endl;
     }
     std::cout<<"type is "<<typeid(f5<int>(4)).name()<<std::endl;
    //  }     else if(std::is_same_v<decltype(f5<int>(4)),int&&>)
    //  {
    //     std::cout<<"is int&& x is"<<f5<int>(4)<<std::endl;//引发悬垂引用
    //  }

    if(std::is_same_v<decltype(f6<int>()),int>)
    {
        std::cout<<"f6 return type is int "<<std::endl;
    }
    if(std::is_same_v<decltype(f6_2<int>()),int&>)
    {
        std::cout<<"f6 return type is int& "<<std::endl;
    }
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


void func_auto()
{
   auto para = [](auto& point1,auto& point2)
   {
    return *point1 > * point2 ? * point1 : *point2;
   };


   auto derefLess =                                //C++14版本
    [](const auto& p1,                          //被任何像指针一样的东西
       const auto& p2)                          //指向的值的比较函数
    { 
        *p1=7;
        return *p1 < *p2; };
   
   auto test_fun2 = [](const int *ptr1,int* const ptr2)
   {
        ptr1=nullptr;
        // *ptr1=2;
        int *ptr11 = new int (3);
   
        const int *ptr3 = ptr11;
        ptr3 = nullptr;
        // *ptr3 = 4; 
   };
//    auto test_fun3 = [](const int &ptr1,int& const ptr2)
//    {
//         // ptr1=nullptr;
//         // *ptr1=2;
//         int *ptr11 = new int (3);
   
//         const int *ptr3 = ptr11;
//         ptr3 = nullptr;
//         // *ptr3 = 4; 
//    };
   auto test_func4 = [](auto&& para1,auto&& para2)
   {

   };
   int x1 = 3;
   int x2 = 4;
   auto x3 = std::make_shared<int>(3);
   auto x4 = std::make_shared<int>(4);
   std::cout<<"para is "<<para(x3,x4)<<std::endl;
   std::cout<<"para is "<<derefLess(&x1,&x2)<<std::endl;
   std::cout<<"para is "<<derefLess(x3,x4)<<std::endl;
}

class TestChainRef{
public:
  int v1;
  int v2;
  int v3; 
  TestChainRef setvalue1(int a)
  {
     this->v1 = a;
     return *this;
  }
  TestChainRef setvalue2(int b)
  {
     this->v2 = b;
     return *this;
  }
  TestChainRef setvalue3(int c)
  {
     this->v3 = c;
     return *this;
  }

};

void test_chain_ref()
{
    TestChainRef* chain = new TestChainRef;
    chain->setvalue1(1).setvalue2(2).setvalue3(3);
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
    func_auto();
    return 0;
}