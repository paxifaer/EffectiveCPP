#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
enum Color{
  red,
  blue,
  green
};

enum class Color2{
  red2,
  blue2,
  green2 = 0xFFFFFF
};

enum Shape : int32_t ;
enum class Shape2 :int32_t;

enum Shape : int32_t {
  reactangle,
  circle
};

enum class Shape2 : int32_t {
  reactangle2,
  circle2
};

template<class T>
  constexpr decltype(auto)infer(T value)
  {
     return static_cast<std::underlying_type_t<T>>(value);
  };//编译期的类型转换器

using ShapeCan = std::tuple<int32_t, int32_t, int32_t>;

template<class T>
  constexpr decltype(auto)infer2(T&& value)
  {
    return static_cast<std::underlying_type_t<T>>(value);
  };



template<class T>
  constexpr decltype(auto)infer3(T&& value)
{
  return static_cast<std::underlying_type_t<T>>(value);
}
int main()
{
  std::vector<int> a{1, 2, 3};  // 原始容器
    
    // 使用不同的变量名来存储查找结果
  auto it = std::find(a.cbegin(), a.cend(), 1);

   

  ShapeCan can1{1,2,3};
  
  std::cout<<std::get<infer(Shape2::circle2)>(can1)<<std::endl;
  std::cout<<std::get<infer(circle)>(can1)<<std::endl;

  
  return 0;
}