//
// Created by boil on 18-10-3.
//

#ifndef RENDU_COMMON_TYPES_H
#define RENDU_COMMON_TYPES_H

#include <stdint.h>
#include <string.h> // memset
#include <string>

#ifndef NDEBUG
#include <assert.h>
#endif

namespace rendu
{
    using std::string;

    inline void memZero(void *p, size_t n)
    {
        memset(p, 0, n);
    }

    //在类型层次结构中 使用implicit_cast(隐式强制转换)作为static_cast(静态强制转换)或const_cast(常量强制转换)的安全版本
    //（i.e.将指向Foo的指针转换为指向SuperclassOfFoo的指针，或指向Foo的常量指针 ）。
    //使用隐式转换时，编译器会检查转换是否安全。
    //这样的显式隐式转换是非常令人惊讶的，在许多情况下，C++需要精确的类型匹配，而不是可转换为目标类型的参数类型。
    //From类型可以被推断出，因此使用 implicit_cast的与使用 static_cast 的语法是相同的，诸如此类：
    //
    //implicit_cast<ToType>(expr)
    //
    template <typename To, typename From>
    inline To implicit_cast(From const &f)
    {
        return f;
    }

    //当您向上转换（即，将指针从Foo类型转换到SuperclassOfFoo类型）时，可以使用implicit_cast<>，
    //因为向上转换总是成功的。
    //当您向下转换 (即，将指针从Foo类型转换为SubclassOfFoo类型)时，static_cast<>并不安全，
    //因为您如何知道指针实际上是SubclassOfFoo类型的？它可以是一个裸Foo，也可以是一个 DifferentSubclassOfFoo类型
    //因此，当您向下转换时，应该使用此宏。
    //在调试模式下，我们使用dynamic_cast<>来再次检查downcast是否合法（如果不合法，我们就死定）。
    //在常规模式下，我们使用static_cast<>更有效。
    //所以，在调试模式下测试，以确保转换是保合法的，这个很重要！

    //这是代码中唯一应该使用dynamic_cast<>的地方.
    //特别是，您不应该使用dynamic_cast来执行RTTI（例如这样的代码：
    //    if (dynamic_cast<Subclass1>(foo)) HandleASubclass1Object(foo);
    //    if (dynamic_cast<Subclass2>(foo)) HandleASubclass2Object(foo);
    //你不应该用这样的方法，而是用另外的方法来设计代码。

    template <typename To, typename From>
    inline To down_cast(From *f) // use like this: down_cast<T*>(foo); 所以我们只接受指针来确保To是From*的子类型。
    {
        if (false)
        {
            implicit_cast<From *, To>(0);
        }

#if !defined(NDEBUG) && !defined(GOOGLE_PROTOBUF_NO_RTTI)
        assert(f == NULL || dynamic_cast<To>(f) != NULL); // RTTI: debug mode only!//此测试仅用于编译时类型检查，在运行时优化后没有开销
#endif
        return static_cast<To>(f);
    }

} // namespace rendu

#endif //RENDU_COMMON_TYPES_H
