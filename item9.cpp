#include<iostream>
#include<type_traits>
#include<stack>
#include<list>

template<class T> 
  using remove_reference_t = typename std::remove_reference<T>::type;
template<class T>
  using add_lvalue_reference_t = typename std::add_lvalue_reference<T>::type;

void func1(int &l)
{
     if(std::is_same_v<remove_reference_t<decltype(l)>,int>)
     {
        std::cout<<" is not lvalue"<<std::endl;
     }

     int a = 0;
     if(std::is_same_v<add_lvalue_reference_t<decltype(a)>,int&>)
     {
         std::cout<<"a  is lvalue"<<std::endl;
     }
}


template<class T>
  using stack1 = std::stack<T>;

template<class T>
  struct stack2{
    typedef std::stack<T> type;
};

template<class T>
  using stack2_t = typename stack2<T>::type;

template<class T>
  struct stack5{
  typedef std::stack<T> type;
};

template<class T>
  void func2(T para)
{
    stack1<T>st1;
    st1.push(para);

    //    typename stack2<T>::type st2;
    stack2<int>::type st2;
    st2.push(para);

    typename stack2<T>::type st3;
    st3.push(para);
}


template<class T>
  struct stack6{
    typedef std::list<std::stack<T>> type;
};

template<class T>
  // using stack6_t = stack6<T>::type;
  using stack6_t = std::list<std::stack<T>>;

int main()
{
    
    int a=0;
    func1(a);

    func2(a);

    return 0;
}