#ifndef BITES_CONCURRENTQUEUE_HPP_INCLUDED
#define BITES_CONCURRENTQUEUE_HPP_INCLUDED

#include <queue>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

namespace bites {

/*!
  The ConcurrentQueue class is a thread-safe queue.
  Code is adapted from original posting by Anthony Williams at
  http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html
*/
template<typename Data>
class ConcurrentQueue
{
private:
    std::queue<Data> the_queue;
    mutable boost::mutex the_mutex;
    boost::condition_variable the_condition_variable;
public:
    //!  Push data onto queue.
    //!  \param data data to be pushed.
    void push(Data const& data)
    {
        boost::mutex::scoped_lock lock(the_mutex);
        the_queue.push(data);
        lock.unlock();
        the_condition_variable.notify_one();
    }

    //!  Test whether the queue is empty.
    //!  \returns whether the queue is empty (i.e. whether its size is zero.)
    bool empty() const
    {
        boost::mutex::scoped_lock lock(the_mutex);
        return the_queue.empty();
    }

    //!  \param popped_value reference to popped value, if successful.
    //!  \returns true if a value was popped, false otherwise (i.e. nothing in the queue.)
    bool try_pop(Data& popped_value)
    {
        boost::mutex::scoped_lock lock(the_mutex);
        if(the_queue.empty())
        {
            return false;
        }
        
        popped_value=the_queue.front();
        the_queue.pop();
        return true;
    }

    //!  Pops value off the queue (waits until queue has value first.)
    //!  \param popped_value reference to popped value.
    void wait_and_pop(Data& popped_value)
    {
        boost::mutex::scoped_lock lock(the_mutex);
        while(the_queue.empty())
        {
            the_condition_variable.wait(lock);
        }
        
        popped_value=the_queue.front();
        the_queue.pop();
    }

    //!  Return size.
    //!  \returns number of elements in the queue.
    typename std::queue<Data>::size_type size()
    {
        boost::mutex::scoped_lock lock(the_mutex);
        return the_queue.size();
    }

};

}  // namespace bites.

#endif  // BITES_CONCURRENTQUEUE_HPP_INCLUDED
