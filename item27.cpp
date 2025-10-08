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
    testImpl(std::forward<T>(x), std::is_integral<std::remove_reference_t<T>>{});
}

// //remove_reference_t只能解引用，decay_t可以更解掉const
// class Person {
// public:
//     template<                       //同之前一样
//         typename T,
//         typename = std::enable_if_t<
//             !std::is_base_of<Person, std::decay_t<T>>::value
//             &&
//             !std::is_integral<std::remove_reference_t<T>>::value
//         >
//     >
//     explicit Person(T&& n)
//     : name(std::forward<T>(n))
//     {
//         //断言可以用T对象创建std::string
//         static_assert(
//         std::is_constructible<std::string, T>::value,
//         "Parameter n can't be used to construct a std::string"
//         );

//         // …               //通常的构造函数的工作写在这

//     }
    
//     // …                   //Person类的其他东西（同之前一样）
// };
//std::is_base_of<A,B> 意思B不是A的同类=或者子类
int main()
{
    test("aaa");
    test(11);
    return 0;
}