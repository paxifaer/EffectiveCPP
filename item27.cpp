#include <iostream>
#include <type_traits>


template<class T>
void testImpl(T&& x, std::false_type)
{
    std::cout<<"this is template"<<std::endl;
}



void testImpl(int x, std::true_type)
{
    std::cout<<"this is int "<<std::endl;
}

template<class T>
void test(T&& x)
{
    testImpl(std::forward<T>(x), std::is_integral_v<std::remove_reference_t<T>>{});
}

int main()
{
    test("aaa");
    test(11);
    return 0;
}