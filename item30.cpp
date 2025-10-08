// - 当模板类型推导失败或者推导出错误类型，完美转发会失败。
// - 导致完美转发失败的实参种类有花括号初始化，作为空指针的`0`或者`NULL`，仅有声明的整型`static const`数据成员，模板和重载函数的名字，位域。

#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;
void f(const vector<int> vec)
{

}
class Fu{
  public:
    static const int pa;
};



void f2(int vec)
{

}
template<class... Args>
void fwd(Args... args)
{
   f(forward<Args>(args)...);
}

template<class... Args>
void fwd2(Args... args)
{
   f2(forward<Args>(args)...);
}



const int Fu::pa = 28;
void test()
{
        f2(Fu::pa);
    fwd2(Fu::pa);
}

int ps(int a, int b)
{

}

int ps(int a)
{
    
}

int f3(int (*pf)(int))
{
    pf(42);
}

template<class... Args>
void fwd3(Args... args)
{
   f3(forward<Args>(args)...);
}
using FunPtrType = int(*)(int);


int f4(vector<int> vec)
{
    // pf(42);
}

template<class... Args>
void fwd4(Args... args)
{
   f4((args)...);
}

int main()
{

    // fwd({1,2,3});//使用模板后，编译器将其推导为initlize_list 而不是vector
    // const int Fu::pa = 28;
    // f2(Fu::pa);
    // fwd2(Fu::pa);
    test();
    
    f3(ps);
    // fwd3(ps);//不是函数指针
    fwd3(static_cast<FunPtrType>(ps));
//感觉模板函数类型推导时候，往下传递参数时候，不会再隐式帮忙类型转换或者构造
    // fwd4({1,2,3});
    f4({1,2,3});
    return 0;
}