// A string like object that points into another piece of memory.
// 对于提供允许客户端轻松传入“const char*”或“string”的接口很有用。
// I wish C++ literals were automatically of type "string".

#ifndef RENDU_STRINGPIECE_H
#define RENDU_STRINGPIECE_H

#include "types.h"
#include <iosfwd> // for ostream forward-declaration

namespace rendu
{

    //用于将C样式的字符串参数传递给函数。
    class StringArg // copyable
    {
    public:
        StringArg(const char *str)
            : str_(str) {}

        StringArg(const std::string& str)
            : str_(str.c_str()) {}

        const char *c_str() const { return str_; }

    private:
        const char *str_;
    };

    class StringPiece
    {
    private:
        const char *ptr_;
        int length_;

    public:
        //我们提供了non-explicit(非显式)的单例构造函数，
        //所以用户可以在需要“stringpiece”的地方传入“const char*”或“string”。
        StringPiece()
            : ptr_(NULL),
              length_(0) {}

        StringPiece(const char *str)
            : ptr_(str),
              length_(static_cast<int>(strlen(ptr_))) {}

        StringPiece(const unsigned char *str)
            : ptr_(reinterpret_cast<const char *>(str)),
              length_(static_cast<int>(strlen(ptr_))) {}

        StringPiece(const string &str)
            : ptr_(str.data()),
              length_(static_cast<int>(str.size())) {}

        StringPiece(const char *offset, int len)
            : ptr_(offset),
              length_(len) {}

        //data()可以返回一个指向带有嵌入NULs的缓冲区的指针，而且返回的缓冲区也可以不为空结尾
        //因此，将data（）传递给期望以NUL结尾的字符串的例程通常是错误的。
        // Use "as_string().c_str()" if you really need to do this.
        // Or better yet, change your routine so it does not rely on NUL termination.
        const char *data() const { return ptr_; }

        int size() const { return length_; }

        bool empty() const { return length_ == 0; }

        const char *begin() const { return ptr_; }

        const char *end() const { return ptr_ + length_; }

        void clear()
        {
            ptr_ = NULL;
            length_ = 0;
        }

        void set(const char *buffer, int len)
        {
            ptr_ = buffer;
            length_ = len;
        }

        void set(const char *str)
        {
            ptr_ = str;
            length_ = static_cast<int>(strlen(str));
        }

        void set(const void *buffer, int len)
        {
            ptr_ = reinterpret_cast<const char *>(buffer);
            length_ = len;
        }

        char operator[](int i) const { return ptr_[i]; }

        void remove_prefix(int n)
        {
            ptr_ += n;
            length_ -= n;
        }

        void remove_suffix(int n)
        {
            length_ -= n;
        }

        bool operator==(const StringPiece &x) const
        {
            return ((length_ == x.length_) &&
                    (memcmp(ptr_, x.ptr_, length_) == 0));
        }

        bool operator!=(const StringPiece &x) const
        {
            return !(*this == x);
        }

#define STRINGPIECE_BINARY_PREDICATE(cmp, auxcmp)                                \
    bool operator cmp(const StringPiece &x) const                                \
    {                                                                            \
        int r = memcmp(ptr_, x.ptr_, length_ < x.length_ ? length_ : x.length_); \
        return ((r auxcmp 0) || ((r == 0) && (length_ cmp x.length_)));          \
    }
        STRINGPIECE_BINARY_PREDICATE(<, <);
        STRINGPIECE_BINARY_PREDICATE(<=, <);
        STRINGPIECE_BINARY_PREDICATE(>=, >);
        STRINGPIECE_BINARY_PREDICATE(>, >);
#undef STRINGPIECE_BINARY_PREDICATE

        int compare(const StringPiece &x) const
        {
            int r = memcmp(ptr_, x.ptr_, length_ < x.length_ ? length_ : x.length_);
            if (r == 0)
            {
                if (length_ < x.length_)
                    r = -1;
                else if (length_ > x.length_)
                    r = +1;
            }
            return r;
        }

        string as_string() const
        {
            return string(data(), size());
        }

        void CopyToString(string *target) const
        {
            target->assign(ptr_, length_);
        }

        // Does "this" start with "x"
        bool starts_with(const StringPiece &x) const
        {
            return ((length_ >= x.length_) && (memcmp(ptr_, x.ptr_, x.length_) == 0));
        }
    };
    
} // namespace rendu

// ------------------------------------------------------------------
//用于创建使用StringPiece的STL容器的函数请记住，StringPiece的生存期最好小于基础字符串或char*的生存期。
//如果不是，则不能安全地将StringPiece存储到STL容器中
// ------------------------------------------------------------------

#ifdef HAVE_TYPE_TRAITS
// This makes vector<StringPiece> really fast for some STL implementations
template <>
struct __type_traits<rendu::StringPiece>
{
    typedef __true_type has_trivial_default_constructor;
    typedef __true_type has_trivial_copy_constructor;
    typedef __true_type has_trivial_assignment_operator;
    typedef __true_type has_trivial_destructor;
    typedef __true_type is_POD_type;
};
#endif

// allow StringPiece to be logged
std::ostream &operator<<(std::ostream &o, const rendu::StringPiece &piece);

#endif //RENDU_STRINGPIECE_H
