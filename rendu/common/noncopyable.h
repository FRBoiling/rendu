//
// Created by boil on 18-10-11.
//

#ifndef RENDU_NONCOPYABLE_H
#define RENDU_NONCOPYABLE_H
namespace rendu {

//  Private copy constructor and copy assignment ensure classes derived from
//  class noncopyable cannot be copied.

//  Contributed by Dave Abrahams

    class noncopyable {
    protected:
        noncopyable() = default;

        ~noncopyable() = default;

//    private:  // emphasize the following members are private
//        noncopyable(const noncopyable &);
//
//        const noncopyable &operator=(const noncopyable &);
    public:
        noncopyable(const noncopyable &)= delete;

        const noncopyable &operator=(const noncopyable &)= delete;
    };

} //namespace rendu;

#endif //RENDU_NONCOPYABLE_H
