// #include <iostream>
// #include <type_traits>

// class Country{
// public:
//   template<class T>
//   void func1(T&&a);

//   // void func1(std::string a);

// private:
/*在指针的世界里有两种特殊情况。一是`void*`指针，因为没办法对它们进行解引用，或者加加减减等。
另一种指针是`char*`，因为它们通常代表C风格的字符串，而不是正常意义下指向单个字符的指针。
这两种情况要特殊处理，在`processPointer`模板里面，我们假设正确的函数应该拒绝这些类型。也即是说，`processPointer`不能被`void*`和`char*`调用。
现在如果使用`void*`和`char*`调用`processPointer`就是无效的，按常理说`const void*`和`const char*`也应该无效，所以这些实例也应该标注`delete`:
```cpp
template<>
void processPointer<const void>(const void*) = delete;

template<>
void processPointer<const char>(const char*) = delete;
```
如果你想做得更彻底一些，你还要删除`const volatile void*`和`const volatile char*`重载版本，另外还需要一并删除其他标准字符类型的重载版本：`std::wchar_t`，`std::char16_t`和`std::char32_t`。
*/ 
/*
不能给特化的成员模板函数指定一个不同于主函数模板的访问级别。
+ 比起声明函数为`private`但不定义，使用*deleted*函数更好
+ 任何函数都能被删除（be deleted），包括非成员函数和模板实例（译注：实例化的函数）
*/ 
// };
// // 正确写法：在类外
// template<>
// void Country::func1<std::string>(std::string&& a) = delete;

//   template<> void Country::func1<int>(int &&a) = delete;
//   template<> void Country::func1<char>(char &&a) = delete;
// template<class T>
//   void Country::func1(T&& a)
// {

// }
//   template<class T>
//   void Country::func1(T&&a)
//   {
//     std::cout<<"use template "<<std::endl;
//   }

//   template<class T>
//   void Country::func1(T&&a)
//   {
//     std::cout<<"use template "<<std::endl;
//   }

// class Vallige{
// public:
//   Vallige() = delete;
//   Vallige(const Vallige&) = delete;
//   Vallige& operator=(Vallige&) = delete;
//   Vallige& operator=(Vallige&&) = delete;
//   Vallige(Vallige&&) = delete;
// };//default>move>copy>canshugouzao




// int main()
// {

//     return 0;
// }