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

    return 0;
}