#include <iostream>
#include <memory>
void f(void*){
    std::cout<<"this is void*"<<std::endl;
}

void f(int){
    std::cout<<"this is int"<<std::endl;
}

void f(bool){
    std::cout<<"this is bool"<<std::endl;
}


void f(long){
    std::cout<<"this is long"<<std::endl;
}


class Wiget{

};

int f1(Wiget* w)
{
    std::cout<<"Wiget* w"<<std::endl;
}
int f2(std::shared_ptr<Wiget> w)
{
    std::cout<<"std::shared_ptr<Wiget> w"<<std::endl;
}
int f3(std::unique_ptr<Wiget> w)
{
    std::cout<<"std::unique_ptr<Wiget> w"<<std::endl;
}

template <class para1,class para2>
decltype(auto) funccluser(para1 pa1,para2 pa2)
{
    pa1(pa2);
};


void func_double(double a)
{

}

void func_int(int a)
{

}



void TestImplicitConvertion()
{
   int a=0;
   double b=1.1;
   funccluser(func_double,a);
   funccluser(func_int,b);
}

int main()
{
    f(NULL);
    f(nullptr);
    auto result1 = f1(0);//这里能够隐式转换成功原因是0被作为空指针常量。换成1就会编译失败
    //  auto result1 = f1(1);
    auto result2 = f2(NULL);
    auto result3 = f3(nullptr);

    // funcclustr(f1,0);
    // funcclustr(f2,NULL);    //加上模版类型推导后，参数就不能隐式转换成指针，导致编译错误
    funccluser(f3,nullptr);  //但是使用nullptr ，该类型就是nullptr或者 std::nullptr_t 可以进一步推导成任意类型的空指针

    TestImplicitConvertion();
    return 0;
}//总结： 0或者NULL 在模板函数作为参数传递时，不会被隐式转换成指针。