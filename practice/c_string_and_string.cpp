#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>

void test_func()
{
    char str[256];
    std::string str2;
    memcpy(str, "aaaa",4);
    // memcpy(str2.data(), str, sizeof(str));
    str2.assign(str, 4);
    //如果是append 就是叠加，如果是+=也是叠加，但是会多一次构造
    char* a = (char*)malloc(str2.size());
    strncpy(a, str, str2.size());
    std::cout<<a<<std::endl;
}

int main()
{
   test_func();
   return 0;
}