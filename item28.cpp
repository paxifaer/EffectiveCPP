// 引用折叠发生在四种情况：
// 模板实例化、auto 推导、typedef / 别名、decltype。

// 折叠规则：
// 有 & → &，全 && → &&。

// 通用引用其实是能折叠的右值引用。

// std::forward 借助引用折叠实现完美转发。
int main()
{
    
    int a=0;
 

    return 0;
}