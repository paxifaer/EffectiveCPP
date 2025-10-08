#include <iostream>
#include <type_traits>

template<class T, class = std::enable_if_t<!std::is_integral_v<std::remove_reference_t<T>>>>
void test(T && x)
{
   std::cout<<"templare "<<x<<std::endl;
}

template<class T, class = std::enable_if_t<std::is_integral_v<std::remove_reference_t<T>>>>
void test(T x)
{
    std::cout<<"this is int "<<x<<std::endl;
}
int main()
{
    test<std::string>("aaa");
    test<int>(12);
    test<short>(12);
    
    return 0;
}