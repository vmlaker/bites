#ifndef __MUTEXED_HPP__
#define __MUTEXED_HPP__

#include <mutex>
#include <bites.hpp>

namespace bites {

/**
   Wrapper around a mutex-protected object.
*/
template<typename T>
class Mutexed {

public:
    /**
       Default constructor.
    */
    Mutexed () {/* Empty. */}

    /**
       Construct and set the mutexed object.
    */
    Mutexed (const T& value)
    {
        set(value);
    }

    /**
       Set the object.
    */
    void set (const T& value)
    {
        std::lock_guard <std::mutex> locker (m_lock);
        m_value = value;
    }

    /**
       Retrieve (a copy of) the object by value.
    */
    T get ()
    {
        std::lock_guard <std::mutex> locker (m_lock);
        return m_value;
    }

private:
    std::mutex m_lock;
    T m_value;
};

}  // namespace bites.

#endif  // __MUTEXED_HPP__
