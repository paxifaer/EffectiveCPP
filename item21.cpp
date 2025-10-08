#include <iostream>
#include <memory>
#include <atomic>
class Widget{
  public:
    Widget(){}
    Widget(const Widget& w) = default;
    Widget(Widget&& w) = default;
    Widget& operator=(const Widget& w) = default;
    Widget& operator=(Widget&& w) = default;
    void SetA(int b)
    {
       a->store(b); 
    }
  private:
    std::atomic<int>* a;
};


int computePriority()
{
    return 1;
}
void processWidget(std::shared_ptr<Widget> spw, int priority)
{
    std::cout<<"test"<<std::endl;
}

int main()
{
    processWidget(std::shared_ptr<Widget>(new Widget), computePriority());/*
    不建议这一种。因为在编译器中，调用顺序为：
    1.new Widget
    2.computePriority
    3.shared_ptr...
    但凡2出了问题，异常等情况。会造成内存泄漏。这是非常特殊的一种情况
    */
    processWidget(std::make_shared<Widget>(), computePriority());
    return 0;
}