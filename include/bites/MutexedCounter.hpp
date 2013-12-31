#ifndef BITES_MUTEXEDCOUNTER_HPP_INCLUDED
#define BITES_MUTEXEDCOUNTER_HPP_INCLUDED

#include <mutex>

namespace bites {

/**
   Thread-safe class-wide counter.
   You can use it, for example, as base class for your 
   bites::Thread implementation to track class-wide counts:

   \code
   
     class MyThread : public bites::Thread, 
                      public bites::MutexedCounter<MyThread> 
     {
     private:
        void run () {
           std::cout << incrCount() << std::endl;

           // Do useful stuff.

           std::cout << decrCount() << std::endl;
        }
     };

   \endcode
   
   Class-specific counting is implemented using 
   "Curiously recurring template pattern" (CRTP):
      http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
*/   
template <typename T>
class MutexedCounter
{
protected:
    /**
       Thread-safely increment the count.
    */
    static int incrCount ()
    {
        std::lock_guard <std::mutex> locker (m_lock);
        return ++m_count;
    }

    /**
       Thread-safely decrement the count.
    */
    static int decrCount ()
    {
        std::lock_guard <std::mutex> locker (m_lock);
        return --m_count;
    }

private:
    /**
       Global lock for count.
    */
    static std::mutex m_lock;

    /**
       Global count.
    */
    static int m_count;
};

template <typename T> std::mutex MutexedCounter<T>::m_lock;
template <typename T> int MutexedCounter<T>::m_count (0);

}  // namespace bites.

#endif  // BITES_MUTEXEDCOUNTER_HPP_INCLUDED
