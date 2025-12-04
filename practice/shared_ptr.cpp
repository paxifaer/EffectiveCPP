#include <iostream>
#include <atomic>

template<class T>
struct ControlBlock{
  T* ptr;
  std::atomic<int> shared_count{1};
  std::atomic<int> weak_count{0};

  ControlBlock(T* p) : ptr(p){}
};

template<class T> class WeakPtr;
template<class T>
class SharedPtr{
  private:
    T* ptr;
    ControlBlock<T>* ctr;

  public:
    SharedPtr(T* p = nullptr) : ptr(p)
    {
        if(p)
          ctr = new ControlBlock(p);
    }
    
    SharedPtr(const WeakPtr<T>& w_ptr)
    {
        ctr = w_ptr.ctr;
        ptr = w_ptr.ptr;
        if(ctr)
          ctr->shared_count.fetch_add(1);
    }

    SharedPtr(const SharedPtr<T>& other)
    {
        ctr = other.ctr;
        ptr = other.ptr;
        if(ctr)
          ctr->shared_count.fetch_add(1);
    }

    SharedPtr& operator=(const SharedPtr<T>& other)
    {
        if(this == &other)
        {
            return *this;
        }
        release();
        ctr = other.ctr;
        ptr = other.ptr;
        if(ctr)
          ctr->shared_count.fetch_add(1);
        return *this;
    }

    SharedPtr(SharedPtr<T>&& other)
    {
        ctr = other.ctr;
        ptr = other.ptr;
        other.ctr = nullptr;
        other.ptr = nullptr;
    }

    SharedPtr& operator=(SharedPtr<T>&& other)
    {
        if(this==&other)
        {
            return *this;
        }
        release();
        ctr = other.ctr;
        ptr = other.ptr;
        other.ctr = nullptr;
        other.ptr = nullptr;
    }

    ~SharedPtr()
    {
        release();
    }
    T* get() const { return ptr; }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    
    int use_count() const { 
        return ctr ? ctr->shared_count.load(std::memory_order_relaxed) : 0; 
    }
    
    bool unique() const { return use_count() == 1; }
private:

    void release()
    {
        if(!ctr)
          return;

        ctr->shared_count.fetch_sub(1);
        if(ctr->shared_count.load()==0)
        {
            delete ptr;
            if(ctr->weak_count.load()==0)
            {
                delete ctr;
            }
        }    
        ptr = nullptr;
        ctr = nullptr;
    }
};


template<class T>
class WeakPtr{
  private:
    ControlBlock<T>* ctr;
    void release_weak()
    {
        if(!ctr)
          return;
        ctr->weak_count.fetch_sub(1);
        if(ctr->weak_count.load()==0)
        {
            ctr = nullptr;
        }
    }

  public:
    WeakPtr(const SharedPtr<T>& other)
    {
        if(!other.ctr)
          ctr = nullptr;
        else 
        {
            ctr = other.ctr;
            ctr->weak_count.fetch_add(1);
        }
    }

    WeakPtr(const WeakPtr<T>& other)
    {
        if(!other.ctr)
          ctr = nullptr;
        else
        {
            ctr = other.ctr;
            ctr->weak_count.fetch_add(1);
        }
    }
    WeakPtr(WeakPtr<T>&& other)
    {
        if(!other.ctr)
          ctr = nullptr;
        else
        {
            ctr = other.ctr;
            other.ctr = nullptr;
        }
    }

    WeakPtr& operator=(WeakPtr<T>& other)
    {
        if(this==other)
          return *this;

        if(other.ctr)
        {
            release_weak();
            ctr = other.ctr;
            ctr->weak_count.fetch_add(1);
        }
    }

    WeakPtr& operator=(WeakPtr<T>&& other)
    {
        if(this==other)
          return *this;
        
        if(other.ctr)
        {
            release_weak()
            ctr = other.ctr;
            other.ctr = nullptr;
        }
    }

    // bool expired() const {
    //     return !ctr || ctr->shared_count.load() == 0;
    // }

    SharedPtr<T> lock()
    {
        if(!ctr)
          return SharedPtr<T>();
        
        auto count = ctr->shared_count;
        while (count > 0) {
            if (ctr->shared_count.compare_exchange_weak(count, count + 1)) {
                SharedPtr<T> sp;
                sp.ctr = ctr;
                return sp;
            }
        }
        
    }


int main()
{
    return 0;
}