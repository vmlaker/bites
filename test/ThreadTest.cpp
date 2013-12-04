/*!
  Test of Thread class.
*/
#include <list>
#include <boost/test/unit_test.hpp>
#include "bites.hpp"

BOOST_AUTO_TEST_SUITE(Thread_Test)

class NullThread : public bites::Thread 
{ 
private: 
    void run() { /* Empty. */ } 
};

// Single thread.
BOOST_AUTO_TEST_CASE(test1)
{
    NullThread tt;
    tt.start();
    tt.join();
    BOOST_CHECK(true);
}

// Two threads.
BOOST_AUTO_TEST_CASE(test2)
{

    // Create the communication queues and threads.
    typedef bites::ConcurrentQueue<bool> CommQueue;
    class TestThread : public bites::Thread {
    public:
        TestThread(CommQueue& output) : m_output(output) { /* Empty. */ };
    private:
        void run() { m_output.push(true); };
        CommQueue& m_output;
    };
    CommQueue qq1, qq2;
    TestThread tt1(qq1);
    TestThread tt2(qq2);

    // Start the threads.
    tt1.start();
    tt2.start();

    // Retrieve results.
    bool result;
    qq1.wait_and_pop(result);
    BOOST_CHECK(result);
    qq2.wait_and_pop(result);
    BOOST_CHECK(result);

    // Join the threads.
    tt1.join();
    tt2.join();
}

BOOST_AUTO_TEST_SUITE_END()
