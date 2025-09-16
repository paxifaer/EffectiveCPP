#include<iostream>
#include <memory>
class Base{
public:
   virtual void Test()
   {
    std::cout<<"test func Base"<<std::endl;
   };
   virtual void Test2()
   {
    std::cout<<"test func Base2"<<std::endl;
   };
      virtual void Test3()
   {
    std::cout<<"test func Base3"<<std::endl;
   };
   Base& operator=(const Base& b)
   {
     if(this==&b)
     {
        return *this;
     }
     //fuzhi
     return *this;
   }
};

class Wiget : public Base
{
public:
   Wiget& operator=(const Wiget& b)
   {
     if(this==&b)
     {
        return *this;
     }
     //fuzhi
     return *this;
   }
   virtual void Test() override
   {
     std::cout<<"test func Wiget"<<std::endl;
   };
   virtual void Test2() 
   {
    a++;
     std::cout<<"test func Wiget2   "<<a<<std::endl;
   };
   virtual void Test4()
   {
    std::cout<<"test func Wget4"<<std::endl;
   };
   int b=0;
private:
  int a=111;
};
/*
1. 基类必须写 virtual
2. 顶层子类可写可不写 virtual
3. 使用override 是为了注明这个函数是重写的，告诉编译器。(不写也行。但是为了出现子类 void func()  基类想重写结果重载了 int func())

+ 基类函数必须是`virtual`
+ 基类和派生类函数名必须完全一样（除非是析构函数)
+ 基类和派生类函数形参类型必须完全一样
+ 基类和派生类函数常量性`const`ness必须完全一样
+ 基类和派生类函数的返回值和异常说明（*exception specifications*）必须兼容
 总而言之 override的作用是防止写错子类的重写函数
*/
int main()
{
    Wiget a;
    Base b = a;
    b.Test2();
    b.Test();

    std::unique_ptr<Base> base_ptr = std::make_unique<Wiget>();
    base_ptr->Test2();
    base_ptr->Test();
    base_ptr->Test3();
    // std::cout<<base_ptr->b<<std::endl;
    // base_ptr->Test4();
    std::unique_ptr<Wiget> widget_ptr = std::make_unique<Wiget>();
    widget_ptr->Test4();
    return 0;
}