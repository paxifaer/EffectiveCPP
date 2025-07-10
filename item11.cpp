#include <iostream>
#include <type_traits>

class Country{
public:
  template<class T>
    void func1(T&&a);
  template<int> void func1(int a) = delete;
  template<char> void func1(char a) = delete;
   void func1(std::string a);

private:

};

template<class T>
  void Country::func1(T&& a)
{

}

void Country::func1(std::string a) = delete;


class Vallige{
public:
  Vallige() = delete;
  Vallige(const Vallige&) = delete;
  Vallige& operator=(Vallige&) = delete;
  Vallige& operator=(Vallige&&) = delete;
  Vallige(Vallige&&) = delete;
};//default>move>copy>canshugouzao




int main()
{

    return 0;
}