#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <algorithm>
void test_func()
{
    char str[256];
    memcpy(str, "abcde", 5);
    std::string str2="aaaaaaa";
    str2.assign(str, 4);
    std::cout<<str2<<std::endl;

    int t1[16];
    memset(t1, 0, 16);
    int t2[16];
    memcpy(t2, t1, 16);
}/*
memcpy适用于简单的POD类型如struct{int int}
chat int 数组 二进制流等最简单的字节型数据。不适用复杂例如STL
*/

class tc{
public:
  explicit  tc(int a):a_(a){};
  tc(){};
  int a_;
  void print()
  {
    std::cout<<"a_ is "<<a_;
  }
  virtual ~tc(){};
};

class tce:public tc{
public:
  tce(){};
  tce(int a):tc(a){};
  int a;
  int b;
  virtual ~tce(){};
};

void test_copy_n()
{
    std::string str;
    str.assign("8888888888888888888", 8);
    std::string str1;
    str1.resize(4);
    std::copy_n(str.data(), 4, str1.data());
    std::cout<<" str1 is "<<str1<<std::endl;
}

void test_copy_n2()
{
   tce t1(3), t2(5);
   tce l[2]{t1, t2};
   tce l2[2];
   std::copy_n(l, 2, l2);
   l2[0].print();
}

int main()
{
   test_func();
   test_copy_n();
   test_copy_n2();
   return 0;
}