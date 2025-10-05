#include <iostream>
class Tester{
  public:
    Tester()
    {

    }
    
    Tester(Tester &tes)
    {
       std::cout<<"this is tester left reference"<<std::endl;
    }

    Tester(Tester &&tes)
    {
       std::cout<<"this is tester right  reference"<<std::endl;
    }

//   private:
};

template<class T>
T&& Forward(T&& t) noexcept {
    return static_cast<T&&>(t);
}
// 没啥用，而且类型转换有问题

template<class T>
T&& Forward(std::remove_reference_t<T>&t) noexcept {
    return static_cast<T&&>(t);
}

template<class T>
constexpr T&& Forward(std::remove_reference_t<T>&& t) noexcept {
    static_assert(!std::is_lvalue_reference_v<T>, 
                  "can't forward an lvalue as an rvalue");
    return static_cast<T&&>(t);
}

// template<class T>
// T&& Forward(std::remove_reference_t<T>& t) noexcept {
//     return static_cast<T&&>(t);
// }


void test_forward()
{

    Tester test;
    Tester test1(std::forward<Tester>(test));//引用折叠
    Tester test2(std::forward<Tester&&>(test1));//引用折叠
    Tester test3(std::move(test2));
    Tester test4(std::forward<Tester&>(test3));//引用折叠
}

void test_Forward()
{

    Tester test;
    Tester test1(Forward<Tester>(test));//引用折叠
    Tester test2(Forward<Tester&&>(test1));//引用折叠
    Tester test3(std::move(test2));
    Tester test4(Forward<Tester&>(test3));//引用折叠
}

typedef struct  test2{
  std::string a = "default";
  std::string b = "default";
} test3;

int main()
{
    test_forward();
    test3 aa;
    aa.a = "100";
    test3 bb;
    bb.a = std::move(aa.a);

    std::cout<<" aa is "<<aa.a<<"  bb is "<<bb.a<<std::endl;
    return 0;
}