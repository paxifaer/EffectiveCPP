#include <iostream>
#include <memory>
using namespace std;

class Wiget{
    public:
      Wiget();
      Wiget(const Wiget& w);
      Wiget(Wiget&& w) noexcept; //impl 形式决不能在.h文件补全形式。因为此时编译器不知道Impl具体内容
      
      Wiget& operator=(const Wiget& w);
      Wiget& operator=(Wiget&& w) noexcept;
      ~Wiget();
      struct Impl;
      std::unique_ptr<Impl> impl_;
      std::shared_ptr<Impl> impl_shared_;
};