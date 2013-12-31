/*!
  Test of MutexedCounter class.
*/

#include <list>
#include <boost/test/unit_test.hpp>
#include "bites.hpp"

BOOST_AUTO_TEST_SUITE(MutexedCounter_Test)

// Thread count.
BOOST_AUTO_TEST_CASE(test1)
{
    // First class.
    class Test1 : public bites::Thread, public bites::MutexedCounter<Test1> 
    {
    private:
        void run () {
            m_count = incrCount();
        }
    public:
        int m_count = 0;
    };

    // Second class.
    class Test2 : public bites::Thread, public bites::MutexedCounter<Test2> 
    {
    private:
        void run () {
            m_count = incrCount();
        }
    public:
        int m_count = 0;
    };

    // Instantiate all classes.
    std::list <bites::Thread*> threads;
    std::list <Test1*> test1s;
    std::list <Test2*> test2s;
    for (int ii=0; ii<100; ++ii){
        auto t1 = new Test1;
        auto t2 = new Test2;
        threads.push_back (t1);
        threads.push_back (t2);
        test1s.push_back (t1);
        test2s.push_back (t2);
    }

    // Start 'em up 'n join 'em.
    for (auto thread : threads) {
        thread->start();
    }
    for (auto thread : threads) {
        thread->join();
    }

    // Count up the totals.
    int total = 0;
    for (auto thread : test1s) {
        total += thread->m_count;
    }
    BOOST_CHECK_EQUAL (total, 5050);
    total = 0;
    for (auto thread : test1s) {
        total += thread->m_count;
    }
    BOOST_CHECK_EQUAL (total, 5050);

    // Delete the threads.
    for (auto thread : threads) {
        delete thread;
    }        
}

BOOST_AUTO_TEST_SUITE_END()
