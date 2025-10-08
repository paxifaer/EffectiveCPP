/*
🔹 1. 缓存场景

问题：

假设你有一个工厂函数 loadWidget(id)，从磁盘/数据库加载一个对象（耗时很大）。

你想让已经加载过的对象能重复使用，而不是重复加载。
👉 就需要 缓存。

困难点：

缓存用 std::shared_ptr 存对象，这样能共享所有权。

但缓存不应该强行延长对象的生命周期（例如：某个对象没人用时，应该能被销毁）。

如果缓存里直接存 std::shared_ptr，即使外面没人用了，对象依然会被缓存持有，导致内存泄漏或缓存无限长大。

解决办法：

缓存内部存 std::weak_ptr。

当有人请求时：

调用 lock() 看缓存里的 weak_ptr 是否还活着。

如果活着，直接复用；

如果对象已经销毁（expired），就重新加载，并更新缓存。

std::shared_ptr<const Widget> fastLoadWidget(WidgetID id) {
    static std::unordered_map<WidgetID, std::weak_ptr<const Widget>> cache;

    auto sp = cache[id].lock();   // 尝试取缓存
    if (!sp) {                    // 已过期或不存在
        sp = loadWidget(id);      // 重新加载
        cache[id] = sp;           // 放进缓存
    }
    return sp;
}


这样：

外部调用者用 shared_ptr 管理生命周期；

缓存内部用 weak_ptr 追踪，但不阻止对象销毁。

🔹 2. 观察者列表（Observer Pattern）

问题：

在观察者模式中，Subject 持有一堆 Observer。

Subject 需要通知所有 Observer，但它 不应该控制 Observer 的生命周期。

如果 Observer 已经销毁，Subject 却还保留指针，就会出现 悬空指针，导致未定义行为。

常见错误做法：

Subject 存原始指针（Observer*）。
👉 一旦 Observer 被销毁，悬空风险。

Subject 存 shared_ptr<Observer>。
👉 会导致 Subject 和 Observer 之间产生 循环引用，内存泄漏。

解决办法：

Subject 内部存 weak_ptr<Observer>。

通知时，先 lock()：

如果能锁定（没过期），就调用 Observer 方法；

如果过期，说明 Observer 已经销毁，直接跳过。

class Observer : public std::enable_shared_from_this<Observer> {
public:
    virtual void onNotify(int data) = 0;
};

class Subject {
    std::vector<std::weak_ptr<Observer>> observers;

public:
    void addObserver(const std::shared_ptr<Observer>& obs) {
        observers.push_back(obs);
    }

    void notifyAll(int data) {
        for (auto it = observers.begin(); it != observers.end(); ) {
            if (auto sp = it->lock()) {   // 观察者还活着
                sp->onNotify(data);
                ++it;
            } else {
                it = observers.erase(it); // 已过期，清理
            }
        }
    }
};


这样：

Observer 的生命周期由外部（可能是 UI、业务逻辑）决定；

Subject 不会阻止 Observer 被销毁；

Subject 访问前能检查是否过期，避免悬空。

✅ 总结

缓存：weak_ptr 保证缓存不会阻止对象销毁 → 节省内存。

观察者模式：weak_ptr 避免循环引用，也能安全检测观察者是否已销毁。

这两个场景的共同点：
👉 需要引用对象，但不想拥有对象的生命周期控制权。
*/ 


int main()
{
    return 0;
}