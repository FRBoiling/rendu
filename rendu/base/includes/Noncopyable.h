//
// Created by boil on 18-10-11.
//

#ifndef RENDU_NONCOPYABLE_H
#define RENDU_NONCOPYABLE_H

namespace rendu
{

    //  Private copy constructor and copy assignment ensure classes derived from
    //  class noncopyable cannot be copied.
    class Noncopyable
    {
    protected:
        Noncopyable() = default;

        ~Noncopyable() = default;

        //    private:  // emphasize the following members are private
        //        noncopyable(const noncopyable &);
        //
        //        const noncopyable &operator=(const noncopyable &);
    public:
        Noncopyable(const Noncopyable &) = delete;

        const Noncopyable &operator=(const Noncopyable &) = delete;
    };

} // namespace rendu

#endif //RENDU_NONCOPYABLE_H
