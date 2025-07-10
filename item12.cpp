#include<iostream>

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
     std::cout<<"test func Wiget2"<<std::endl;
   };
};

int main()
{
    Wiget a;
    Base b = a;
    return 0;
}