#include "item22.h"

struct Wiget::Impl{
  std::string topic;
  std::string payload;
};

Wiget::Wiget() : impl_(std::make_unique<Wiget::Impl>()), impl_shared_(std::make_shared<Wiget::Impl>()) 
{
}

Wiget::Wiget(const Wiget& w)
{
   impl_ = std::make_unique<Wiget::Impl>(*w.impl_);//新内存
   impl_shared_ = w.impl_shared_;
}

Wiget::Wiget(Wiget&& w) noexcept : impl_(std::move(w.impl_)), impl_shared_(std::move(w.impl_shared_))  //impl 形式决不能在.h文件补全形式。因为此时编译器不知道Impl具体内容
{
}

Wiget& Wiget::operator=(const Wiget& w) 
{
    if(this != &w)
    {
      impl_ = std::make_unique<Wiget::Impl>(*w.impl_);
      impl_shared_ = w.impl_shared_;
    }
    return *this;
}

Wiget& Wiget::operator=(Wiget&& w) noexcept
{
   if(this != &w)
   {
     impl_ = std::move(w.impl_);
     impl_shared_ = (std::move(w.impl_shared_));
   }
   return *this;
}
Wiget::~Wiget()//需要编译器知道
{
}
// shared_ptr 的删除逻辑是 类型无关（运行时） 的，
// unique_ptr 的删除逻辑是 类型相关（编译期） 的。

int main()
{
    return 0;
}