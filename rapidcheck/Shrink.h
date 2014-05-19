#pragma once

#include <type_traits>

namespace rc {

//! Instances of this class are used to implement shrinking. A \c ShrinkIterator
//! type \c T successively yields possible shrinks of some value of that type
//! until all possibilities are exhausted.
template<typename T>
class ShrinkIterator
{
public:
    //! Returns \c true if this \c ShrinkIterator has more values or \c false if
    //! all possible shrinks have been exhausted.
    virtual bool hasNext() const = 0;

    //! Returns the next possible shrink value. The result of calling this
    //! method if \c hasNext returns false is undefined.
    virtual T next() = 0;

    virtual ~ShrinkIterator() = default;
};

//! \c std::unique_ptr to ShrinkIterator
template<typename T>
using ShrinkIteratorUP = std::unique_ptr<ShrinkIterator<T>>;

//! Empty shrink iterator which always returns \c false from \c hasNext.
template<typename T> class NullIterator;

//! Shrinker for integer types.
template<typename T> class DivideByTwoIterator;

//! Shrinks collections by removal of each element in turn.
template<typename T> class RemoveElementIterator;

//! See \c unfold
template<typename T,
         typename I,
         typename Predicate,
         typename Iterate>
class UnfoldIterator;

//! Takes an iterate functor and a stop predicate. To yield each new value, the
//! iterate functor is called with an iterator value and yields a tuple of the
//! next shrink as well as a new iterator value. This is repeated until the
//! predicate returns false for the iterator value.
//!
//! @param initial    The initial iterator value.
//! @param predicate  The stop predicate.
//! @param iterate    The iterate functor.
template<typename I,
         typename Predicate,
         typename Iterate>
ShrinkIteratorUP<typename std::result_of<Iterate(I)>::type::first_type>
unfold(I initial, Predicate predicate, Iterate iterate);

} // namespace rc

#include "detail/Shrink.hpp"
