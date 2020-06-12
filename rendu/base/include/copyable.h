//
// Created by boil on 18-10-3.
//

#ifndef RENDU_COPYABLE_H
#define RENDU_COPYABLE_H

namespace rendu
{
    /// A tag class emphasises the objects are copyable.
    /// The empty base class optimization applies.
    /// Any derived class of copyable should be a value type.
    class copyable
    {
    protected:
        copyable() = default;
        ~copyable() = default;
    };

} // namespace rendu

#endif //RENDU_COPYABLE_H
