// Test of ConcurrentCounter class.

#include <chrono>
#include <boost/test/unit_test.hpp>
#include "bites.hpp"

BOOST_AUTO_TEST_SUITE(ConcurrentCounter_Test)

// Serial use of the counter.
BOOST_AUTO_TEST_CASE(test1)
{
    bites::ConcurrentCounter<char> counter;
    
    BOOST_CHECK(counter.size() == 0);
    BOOST_CHECK(counter.count('a') == 0);
    BOOST_CHECK(counter.has_max('a', 2) == false);
    BOOST_CHECK(counter.size() == 1);
    BOOST_CHECK(counter.count('a') == 1);
    BOOST_CHECK(counter.has_max('a', 2) == false);
    BOOST_CHECK(counter.size() == 1);
    BOOST_CHECK(counter.count('a') == 2);
    BOOST_CHECK(counter.has_max('a', 2) == true);
    BOOST_CHECK(counter.size() == 0);
    BOOST_CHECK(counter.count('a') == 0);
}

void f(bites::ConcurrentCounter<char>* counter, char letter, int count){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 500);
    std::chrono::milliseconds dura( dis(gen) );
    std::this_thread::sleep_for( dura );
    counter->has_max(letter, count-1);
}

// Multi-use of the counter.
BOOST_AUTO_TEST_CASE(test2)
{
    bites::ConcurrentCounter<char> counter;
    const char LETTERS [] = {'a', 'b', 'c'}; 
    const int THREADS_PER_LETTER = 1000;
    std::list< std::thread* > threads;

    for(int ii=0; ii<THREADS_PER_LETTER; ++ii){
        for(auto letter : LETTERS){
            auto thread = new std::thread(f, &counter, letter, THREADS_PER_LETTER);
            threads.push_back(thread);
        }
    }

    for(auto thread : threads){
        thread->join();
    }

    for(auto letter : LETTERS){
        BOOST_CHECK(counter.count(letter) == 0);
    }
    BOOST_CHECK(counter.size() == 0);
}

BOOST_AUTO_TEST_SUITE_END()
