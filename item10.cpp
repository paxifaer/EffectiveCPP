#include <iostream>
#include <tuple>

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
  };

using ShapeCan = std::tuple<int32_t, int32_t, int32_t>;

int main()
{
  
  ShapeCan can1{1,2,3};
  
  std::cout<<std::get<infer(Shape2::circle2)>(can1)<<std::endl;
  std::cout<<std::get<infer(circle)>(can1)<<std::endl;

  
  return 0;
}