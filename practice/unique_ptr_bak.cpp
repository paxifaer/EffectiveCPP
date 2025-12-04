#include <iostream>

template<class T>
class UniquePtr{
  private:
    T* ptr;
  public:
    
    UniquePtr(T* p): ptr(p)
    {}
    
    UniquePtr& operator=(const UniquePtr&) = delete;
    UniquePtr& UniquePtr(const UniquePtr&) = delete;

    UniquePtr& operator=(UniquePtr&& other)
    {
        if(this!=&other)
        {
            delete ptr;
            ptr = other.release();
        }
        return *this;
    }

    UniquePtr(UniquePtr&& other)
    {
        if(this!=&other)
        {
            delete ptr;
            ptr = other.release();
        } 
    }

    T* release()
    {
        auto tmp = ptr;
        ptr = nullptr;
        return tmp;
    }

    T* operator->()
    {
        return ptr;
    }

    T* get()
    {
        return ptr;
    }
};

int main()
{
    return 0;
}