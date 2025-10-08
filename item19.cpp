#include <iostream>
#include <memory>
class Base{
  public:
    Base(){};
    virtual ~Base(){
       std::cout<<"delete base"<<std::endl;
    };
};

class ExP : public Base{
    public:
      ExP(){}

      ~ExP(){
               std::cout<<"delete ExP"<<std::endl;
      }
};

void log()
{
    std::cout<<"delete a pointer"<<std::endl;
}

/*
1.shared_ptr 两倍原始指针大小(两个指针，一个引用记数。一个原始指针)
2.引用计数指针指向控制块，shared_ptr新建时每次使用unique_ptr或者原始指针就会新建一个控制块。导致的问题是，最后可能重复析构。
3.shared_ptr的deleter分配在堆里面，可能内存无限大。且相同类但是不同deleter可以被视为同一种shared_ptr.
4.class内存this存储shared_ptr时候，为了避免新建控制块，可以使用std::enable_this_from_shared
*/ 


class Wiget : public std::enable_shared_from_this<Wiget>
{
  public:
    Wiget(){};
    void process()
    {
        auto ptr = shared_from_this();
    }
};
int main()
{ 
    auto deleter = [](Base *p)
    {
       log();
       delete p;
    };

    // std::unique_ptr<Base, decltype(deleter)> p(nullptr, deleter);
    // std::unique_ptr<ExP, decltype(deleter)> p2(nullptr, deleter);
    std::unique_ptr<Base, decltype(deleter)> p (new Base, deleter);
    std::unique_ptr<Base, decltype(deleter)> p2 (new ExP, deleter);
    std::shared_ptr<Base> p3(std::move(p2));
    std::shared_ptr<Base> p4(new ExP, deleter);
    return 0;
}