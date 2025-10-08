/*C++11 起，特殊成员函数的生成规则更复杂。编译器不再盲目帮你生成“可能错误的函数”
，而是更保守。最好的做法是：如果你希望类能被正常拷贝/移动，显式声明 = default，不要依赖编译器的“暗示”。
*/ 
#include <iostream>

class Wiget{

public:
   Wiget(){};
   Wiget(const Wiget& w)
   {
      this->value1 = w.value1;
      this->value2 = w.value2;
   };

    Wiget(Wiget&& w)
   {
      this->value1 = w.value1;
      w.value1 = 0;
      this->value2 = w.value2;
      w.value2 = 0;
   };

   Wiget& operator=(const Wiget& w)
   {
      if(this == &w)
      {
        return *this;
      }
      this->value1 = w.value1;
      this->value2 = w.value2;
      return *this;
   }

   Wiget& operator=(Wiget&&w)
   {
      if(this == &w)
      {
        return *this;
      }
      this->value1 = w.value1;
      w.value1 = 0;
      this->value2 = w.value2;
      w.value2 = 0;
      return *this;
   }

private:
  int value1=0;
  int value2=0;

};

int main()
{

    return 0;
}