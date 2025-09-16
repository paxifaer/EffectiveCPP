// #include <iostream>
// #include <type_traits>
// #include <utility>
// #include <memory>
// #include<stdio.h>
// #include <future>
// #include <functional>
// #include <queue>

// template<typename T>
// void f(T* param) {
//     if (std::is_same_v<T, int>) {
//         std::cout << "T is int, param is int*\n";
//     } else if (std::is_same_v<T, const int>) {
//         std::cout << "T is const int, param is const int*\n";
//     }
// }

// template<typename T>
// void f2(T& param)
// {
    
// }

// template<typename T>
// void f3(T param)
// {
//     if(std::is_same<T,const char* const>::value)
//     {
//         std::cout << "const char* const\n";
//     }
//     else if(std::is_same_v<T,const char* >)
//     {
//         std::cout << "const char*\n";
//     }
//     else if(std::is_same_v<T, char* >)
//     {
//         std::cout << " char*\n";
//     }
// }               //仍然以传值的方式处理param

// const char* const ptr =         //ptr是一个常量指针，指向常量对象 
//     "Fun with pointers";

// template<class T>
// auto&& f4(T &&para)
// {
     
//     int x=3;
//     return x;
// }

// template<class T>
// decltype(auto) f5(T &&para)
// {
     
//     int x=3;
//     return std::forward<T>((x));

// }

// template<class T>
// decltype(auto) f6()
// {
//     int x=3;
//     return x;
// }

// template<class T>
// decltype(auto) f6_2()//decltype((value)) (value)被识别为一个表达式
// {
//     int x=3;
//     return (x);
// }

// void test_decltype()
// {
//      if(std::is_same_v<decltype(f4(4)),int&>)
//      {
//         std::cout<<"f4 is int&"<<std::endl;
//      }
//      else if(std::is_same_v<decltype(f4(4)),int>)
//      {
//         std::cout<<"f4 is int"<<std::endl;
//      }



//      if(std::is_same_v<decltype(f5<int>(4)),int&>)
//      {
//         std::cout<<"f5 is int&"<<std::endl;
//      }
//      else if(std::is_same_v<decltype(f5<int>(4)),int>)
//      {
//         std::cout<<"f5 is int"<<std::endl;
//      }    else if(std::is_same_v<decltype(f5<int>(4)),int&&>)
//      {
//         std::cout<<"f5 is int&&"<<std::endl;
//      }
//      std::cout<<"type is "<<typeid(f5<int>(4)).name()<<std::endl;
//     //  }     else if(std::is_same_v<decltype(f5<int>(4)),int&&>)
//     //  {
//     //     std::cout<<"is int&& x is"<<f5<int>(4)<<std::endl;//引发悬垂引用
//     //  }

//     if(std::is_same_v<decltype(f6<int>()),int>)
//     {
//         std::cout<<"f6 return type is int "<<std::endl;
//     }
//     if(std::is_same_v<decltype(f6_2<int>()),int&>)
//     {
//         std::cout<<"f6 return type is int& "<<std::endl;
//     }
// }

// void process(int& x)  { std::cout << "左值: " << x << std::endl; }
// void process(int&& x) { std::cout << "右值: " << x << std::endl; }

// // 中间转发函数
// template<typename T>
// void relay(T&& arg) {
//     process(std::forward<T>(arg)); // 完美转发
// }

// std::queue<std::function<void()>> que;

// // template<class T, class ...Args>
// //   decltype(auto) enqueue(T&& func, Args&&... args)
// //   {
// //      using ReturnType = decltype(func(args...));
// //      auto task = std::make_shared<std::packaged_task<ReturnType()>>
// //        (std::bind(std::forward<T>(func), std::forward<Args>(args)...));
// //     std::function<void()> func =    
// //        (std::bind(std::forward<T>(func), std::forward<Args>(args)...));
// //     auto func = [&]()
// //     {
// //        (*task)();
// //     }
// //     que.push(func);
// //   }
// void test_forward()
// {


//     int x = 10;
//     relay(x);       // 输出：左值: 10
//     relay(20);      // 输出：右值: 20
//     relay(std::move(x)); // 输出：右值: 10

// }


// void func_auto()
// {
//    auto para = [](auto& point1,auto& point2)
//    {
//     return *point1 > * point2 ? * point1 : *point2;
//    };


//    auto derefLess =                                //C++14版本
//     [](const auto& p1,                          //被任何像指针一样的东西
//        const auto& p2)                          //指向的值的比较函数
//     { 
//         *p1=7;
//         return *p1 < *p2; };
   
//    auto test_fun2 = [](const int *ptr1,int* const ptr2)
//    {
//         ptr1=nullptr;
//         // *ptr1=2;
//         int *ptr11 = new int (3);
   
//         const int *ptr3 = ptr11;
//         ptr3 = nullptr;
//         // *ptr3 = 4; 
//    };
// //    auto test_fun3 = [](const int &ptr1,int& const ptr2)
// //    {
// //         // ptr1=nullptr;
// //         // *ptr1=2;
// //         int *ptr11 = new int (3);
   
// //         const int *ptr3 = ptr11;
// //         ptr3 = nullptr;
// //         // *ptr3 = 4; 
// //    };
//    auto test_func4 = [](auto&& para1,auto&& para2)
//    {

//    };
//    int x1 = 3;
//    int x2 = 4;
//    auto x3 = std::make_shared<int>(3);
//    auto x4 = std::make_shared<int>(4);
//    std::cout<<"para is "<<para(x3,x4)<<std::endl;
//    std::cout<<"para is "<<derefLess(&x1,&x2)<<std::endl;
//    std::cout<<"para is "<<derefLess(x3,x4)<<std::endl;
// }

// class TestChainRef{
// public:
//   int v1;
//   int v2;
//   int v3; 
//   TestChainRef setvalue1(int a)
//   {
//      this->v1 = a;
//      return *this;
//   }
//   TestChainRef setvalue2(int b)
//   {
//      this->v2 = b;
//      return *this;
//   }
//   TestChainRef setvalue3(int c)
//   {
//      this->v3 = c;
//      return *this;
//   }

// };

// void test_chain_ref()
// {
//     TestChainRef* chain = new TestChainRef;
//     chain->setvalue1(1).setvalue2(2).setvalue3(3);
// }









// // #############################  item 7 #####################################
// //本章节主要讲解 花括号构造时的优先级{}，类里面没有std::initializer_list<double> ，使用{}构造会根据类型进入不同的构造函数中，但是当类里面存在Wiget(std::initializer_list<double> list)时
// // 无论怎么构造都会进去Wiget(std::initializer_list<double> list)里面
// class Wiget{
//     public:
//       Wiget(int a,double d){
//          std::cout<<"use para func "<<std::endl;
//       }
//     //   Wiget(int a,double d){}
//       Wiget(std::initializer_list<double> list){
//         std::cout<<"use initializer_list "<<std::endl;
//       }
//       operator double(){
//         std::cout<<"operator double"<<std::endl;
//       }
//       operator float(){
//         std::cout<<"operator float"<<std::endl;
//       }
//      operator int(){
//         std::cout<<"operator int"<<std::endl;
//       }
//     //   Wiget(Wiget&& w){
//     //        std::cout<<"use Wiget&&"<<std::endl;
//     //   }
// };



// template<typename T,            //要创建的对象类型
//          typename... Ts>        //要使用的实参的类型
// void 
// // decltype(auto) 
// doSomeWork(T a, Ts&&... params)
// {
//     // T localObject(std::forward<Ts>(params)...);
//     // for(auto& para1:localObject)
//     // {
//     //     std::cout<<"para1 is "<<para1<<" ";
//     // }
//     std::cout<<std::endl;
//     T localObject2{std::forward<Ts>(params)...};
//     for(auto& para2:localObject2)
//     {
//         std::cout<<"para2 is "<<para2<<" ";
//     }
//     std::cout<<std::endl;


//     T localObject3{(params)...};
//     for(auto& para3:localObject3)
//     {
//         std::cout<<"para3 is "<<para3<<" ";
//     }
//     std::cout<<std::endl;

//     T localObject4((params)...);
//     for(auto& para4:localObject4)
//     {
//         std::cout<<"para4 is "<<para4<<" ";
//     }
//     std::cout<<std::endl;
//     // std::vector<T> vec(std::forward<Ts>(params)...);
//     // std::vector<T> vec2{std::forward<Ts>(params)...};
// } 

// // template<class... args>



// void Item7Func()
// {
//     Wiget w1(1,2);
//     Wiget w2{1,2};
//     Wiget w3(w1);
//     Wiget w4{w2};
//     Wiget w5(std::move(w2));
//     Wiget w6{std::move(w2)};
// }
// #include <vector>
// void Item7Func2()
// {
//     // doSomeWork<std::vector<int>>(10, 20);
//     // doSomeWork<std::vector<int>>(10, 20);
//     // doSomeWork<std::vector<int>,int,double>(10, 20);
//     std::vector<int> a{1,2,3};
//     doSomeWork(a,10, 20);//另外一点值得注意，template关于<>括号注明函数类型的使用很灵过，当里面参数有实际注入要么<>内部按照顺序注明，或者在()里面放入参数可以自动推导 
//     //一般不建议<>声明一些，再在()里面存放另外一些，很容易让人误解。
//     // doSomeWork<std::vector<int>>({10,20});
//     //  doSomeWork<std::vector<int>>(10, 20);
// }

// // #############################  item 7 #####################################



// int main() {
//     // int x = 27;
//     // const int *px = &x;

//     // // f(&x); // 输出：T is int, param is int*
//     // // f(px); // 输出：T is const int, param is const int*
//     // // int x=3;
//     // // f2(x);
//     // // f2(std::move(x));
    
//     // const char* const pa = "aaa";

//     // // f3(pa);
//     // // test_decltype();
//     // // test_forward();
//     // // func_auto();
//     // // Item7Func();
//     // Item7Func2();

//     return 0;
// }