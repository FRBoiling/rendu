//
// Created by boil on 18-11-2.
//

#include <cstdio>
#include <rendu/log/Logger.h>

using namespace rendu;
using namespace rendu::log;

class MyString {
public:
    MyString(const char *data = nullptr);

    MyString(const MyString &other);

    MyString(MyString &&other) noexcept;

    ~MyString();

    MyString &operator=(const MyString &other);

    MyString &operator=(const char *other);

    MyString &operator=(MyString &&other) noexcept;

    bool operator==(const MyString &other) const;

    size_t size() const;        //获取长度
    const char *c_str() const;    //获取C字符串
private:
    char *data_;
    size_t length_;
};

MyString::MyString(const char *data) {
    if (data == nullptr) {
        length_ = 0;
        data_ = new char[1];
        *data_ = '\0';
    } else {
        length_ = strlen(data);
        data_ = new char[length_ + 1];
        strcpy(data_, data);
    }
    LOG_DEBUG << this << " Constructor " << data_;
}

MyString::~MyString() {
    LOG_DEBUG << this << " Destructor " << data_;
    delete[] data_;
    length_ = 0;
}

MyString::MyString(const MyString &other) {
    length_ = other.size();
    data_ = new char[length_ + 1];
    strcpy(data_, other.c_str());
    LOG_DEBUG << this << " Copy Constructor " << data_;
}


MyString::MyString(MyString &&other) noexcept {
    length_ = other.size();
    data_ = other.data_;
    other.data_ = nullptr;
    LOG_DEBUG << this << " Move constructor";
}

MyString &MyString::operator=(const MyString &other) {
    LOG_DEBUG << this << " MyString operator=";

    if (this == &other) return *this;
    if (!data_) delete[]data_;
    length_ = other.length_;

    data_ = new char[length_ + 1];
    strcpy(data_, other.c_str());

    return *this;
}

MyString &MyString::operator=(const char *other) {
    LOG_DEBUG << this << " const char operator=";
    if (data_ == other) return *this;
    if (!data_) delete[]data_;
    length_ = strlen(other);

    data_ = new char[length_ + 1];
    strcpy(data_, other);

    return *this;
}


MyString &MyString::operator=(MyString &&other) noexcept {
    LOG_DEBUG << this << " move operator=";

    if (this == &other) return *this;
    if (!data_) delete[]data_;
    length_ = other.length_;

    data_ = other.data_;
    other.data_ = nullptr;

    return *this;
}

inline bool MyString::operator==(const MyString &other) const {
    if (length_ != other.length_) return false;
    return strcmp(data_, other.data_) ? false : true;
}


inline size_t MyString::size() const {
    return length_;
}

inline const char *MyString::c_str() const//获取C字符串
{
    return data_;
}

int main() {
    Logger::init();

    // 测试：默认构造
    MyString s1;

    // 测试：传参构造
    MyString s2("hello world");

    // 测试：拷贝构造
    MyString s3(s1);

    // 测试：移动构造
    MyString s4(std::move(s3));

    // 测试：拷贝赋值
    s1 = s4;

    // 测试：移动赋值
    s1 = std::move(s4);

}