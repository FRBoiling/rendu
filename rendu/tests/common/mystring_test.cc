//
// Created by boil on 18-11-2.
//

#include <cstdio>
#include <rendu/log/Logger.h>

using namespace rendu::log;

class MyString {
public:
    MyString(const char *data = nullptr);

    MyString(const MyString &myString);

    ~MyString();

    bool &operator==(const MyString &myString) const;

    MyString &operator=(const MyString &myString);

    size_t size() const;        //获取长度
    const char *c_str() const;    //获取C字符串
private:
    char *data_;
    size_t length_;
};

MyString::MyString(const char *data) {
    LOG_DEBUG << "MyString()";
    if (data == nullptr) {

    } else {
        length_ = strlen(data);
        data_ = new char[length_ + 1];
        strcpy(data_, data);
    }
}

MyString::~MyString() {
    delete[] data_;
    length_ = 0;
    LOG_DEBUG << "~MyString()";
}

MyString::MyString(const MyString &myString) {
    length_ = myString.size();
    data_ = new char[length_ + 1];
    strcpy(data_, myString.c_str());
}

MyString &MyString::operator=(const MyString &myString) {

}

inline size_t MyString::size() const {
    return length_;
}

inline const char* MyString::c_str() const//获取C字符串
{
    return data_;
}