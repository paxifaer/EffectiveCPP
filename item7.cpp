#include <iostream>
#include <iostream>
#include <utility> // for std::move

class Animal {
private:
    int* a; // 动态资源示例

public:
    // 默认构造函数
    Animal() : a(new int(0)) {}

    // 带参数构造
    Animal(int val) : a(new int(val)) {}

    // 拷贝构造
    Animal(const Animal& ani) : a(new int(*ani.a)) {
        std::cout << "Copy constructor called\n";
    }

    // 移动构造
    Animal(Animal&& ani) noexcept : a(ani.a) {
        ani.a = nullptr; // 源对象释放指针
        std::cout << "Move constructor called\n";
    }

    // 拷贝赋值
    Animal& operator=(const Animal& ani) {
        if (this != &ani) {
            delete a;
            a = new int(*ani.a);
            std::cout << "Copy assignment called\n";
        }
        return *this;
    }

    // 移动赋值
    Animal& operator=(Animal&& ani) noexcept {
        if (this != &ani) {
            delete a;       // 释放当前资源
            a = ani.a;      // 移动资源
            ani.a = nullptr; // 源对象置空
            std::cout << "Move assignment called\n";
        }
        return *this;
    }

    // 析构函数
    ~Animal() {
        delete a;
    }

    void print() const {
        if(a)
            std::cout << "Value: " << *a << "\n";
        else
            std::cout << "Value: nullptr\n";
    }
};

// 测试
int main() {
    Animal a1(10);
    Animal a2 = a1;        // 拷贝构造
    Animal a3 = std::move(a1); // 移动构造
    Animal a4;
    a4 = a2;               // 拷贝赋值
    a4 = std::move(a3);    // 移动赋值

    a2.print();
    a3.print();
    a4.print();

    return 0;
}

/*
只有当没办法把括号初始化中实参的类型转化为`std::initializer_list`时，编译器才会回到正常的函数决议流程中。
比如我们在构造函数中用`std::initializer_list<std::string>`代替`std::initializer_list<bool>`，这时非`std::initializer_list`构造函数将再次成为函数决议的候选者，
因为没有办法把`int`和`bool`转换为`std::string`:
初次之外{}花括号的对象初始化，一般更倾向于initializer_list
可能编译器认为{}就是intialializer_list



template<typename T,            //要创建的对象类型
         typename... Ts>        //要使用的实参的类型
void doSomeWork(Ts&&... params)
{
    create local T object from params...
    …
} 
````
在现实中我们有两种方式实现这个伪代码（关于`std::forward`请参见[Item25](../5.RRefMovSemPerfForw/item25.md)）：
````cpp
T localObject(std::forward<Ts>(params)...);             //使用圆括号
T localObject{std::forward<Ts>(params)...};             //使用花括号
````
考虑这样的调用代码：
````cpp
std::vector<int> v; 
…
doSomeWork<std::vector<int>>(10, 20);
````
如果`doSomeWork`创建`localObject`时使用的是圆括号，`std::vector`就会包含10个元素。如果`doSomeWork`创建`localObject`时使用的是花括号，`std::vector`就会包含2个元素。哪个是正确的？`doSomeWork`的作者不知道，只有调用者知道。
*/ 