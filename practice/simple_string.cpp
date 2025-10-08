#include <iostream>
#include <cstring>  // for strlen, memcpy
#include <cstdlib>  // for malloc, free

class SimpleString {
private:
    char* data_;
    size_t size_;
    size_t capacity_;

    void ensure_capacity(size_t new_size) {
        if (new_size > capacity_) {
            size_t new_capacity = new_size * 2;
            char* new_data = (char*)malloc(new_capacity + 1); // +1 for '\0'
            if (data_) {
                memcpy(new_data, data_, size_);
                free(data_);
            }
            data_ = new_data;
            capacity_ = new_capacity;
        }
    }

public:
    // 默认构造
    SimpleString() : data_(nullptr), size_(0), capacity_(0) {}

    // 从 C 字符串构造
    SimpleString(const char* str) {
        size_ = strlen(str);
        capacity_ = size_;
        data_ = (char*)malloc(capacity_ + 1);
        memcpy(data_, str, size_);
        data_[size_] = '\0';
    }

    // 析构
    ~SimpleString() {
        if (data_) free(data_);
    }

    // 获取大小
    size_t size() const { return size_; }

    // 返回 C 字符串
    const char* c_str() const { return data_ ? data_ : ""; }

    // 追加操作
    void append(const char* str) {
        size_t len = strlen(str);
        ensure_capacity(size_ + len);
        memcpy(data_ + size_, str, len);
        size_ += len;
        data_[size_] = '\0';
    }

    // += 重载
    SimpleString& operator+=(const char* str) {
        append(str);
        return *this;
    }

    // 输出重载
    friend std::ostream& operator<<(std::ostream& os, const SimpleString& s) {
        os << s.c_str();
        return os;
    }
};

int main() {
    SimpleString s1("Hello");
    SimpleString s2("World");
    s1 += ", ";
    s1 += s2.c_str();  // 可以用 C 风格字符串追加
    std::cout << s1 << std::endl;  // 输出: Hello, World
}
