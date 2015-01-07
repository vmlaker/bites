#ifndef BITES_CONCURRENTCOUNTER_HPP_INCLUDED
#define BITES_CONCURRENTCOUNTER_HPP_INCLUDED

#include <map>
#include <mutex>
#include <thread>

namespace bites {

/**
   A thread-safe counter of keys.

   \code
   
     bites::ConcurrentCounter<char> c1;

     c1.has_max('a', 2);  // Returns false because the count of 'a' was 0 (less than 2)

     // The count of 'a' is now 1

     c1.has_max('a', 2);  // Returns false because the count of 'a' was 1 (less than 2)

     // The count of 'a' is now 2

     c1.has_max('a', 2);  // Returns true because the count of 'a' was 2 (reached max)

     // The count of 'a' is now 0

   \endcode
*/   
template<typename T>
class ConcurrentCounter
{
private:
    std::map<T, unsigned> m_map;
    std::mutex m_mutex;
public:
    /**
       Thread-safely query the counter for whether the count
       for *key* has reached (or exceeded) the maximum. If the count is 
       less than the maximum, increment the count and return **false**.
       Otherwise, reduce the count to zero and return **true**.

       @param  key        The key to query
       @param  max_count  Maximum count allowed
       @returns  **false** if the count was less than given maximum, **true** otherwise.
    */
    bool has_max(const T& key, unsigned max_count){

        // Apply mutual exclusion.
        std::lock_guard<std::mutex> lock(m_mutex);

        unsigned cur_count = 0;
        auto search = m_map.find(key);
        if(search != end(m_map)){
            cur_count = search->second;
            if(cur_count < max_count){
                search->second++;
                return false;
            }
            m_map.erase(search);
            return true;
        }
        if(max_count > 0){
            m_map.insert({key, 1});
            return false;
        }
    }

    /**
       Thread-safely query the number of keys in the counter.

       @returns  Number of keys in the counter
    */
    typename std::map<T, unsigned>::size_type size(){
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_map.size();
    }

    /**
       Thread-safely query the current count for given key.

       @param  key  The key to query
       @returns  Current count for the given key
    */
    typename std::map<T, unsigned>::size_type count(const T& key){
        std::lock_guard<std::mutex> lock(m_mutex);
        auto search = m_map.find(key);
        if(search != end(m_map)){
            return search->second;
        }
        return 0;
    }
        
};

}  // namespace bites.

#endif  // BITES_CONCURRENTCOUNTER_HPP_INCLUDED
