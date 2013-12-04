// Test of ConcurrentQueue class.

#include <queue>
#include <thread>
#include <boost/test/unit_test.hpp>
#include "ConcurrentQueue.hpp"

BOOST_AUTO_TEST_SUITE(ConcurrentQueue_Test)

// Serial use of the queue.
BOOST_AUTO_TEST_CASE(test1)
{
    bites::ConcurrentQueue<char> cc;
    char input;
    char output;
    bool result;

    BOOST_CHECK(cc.size() == 0);
    result = cc.try_pop(output);
    BOOST_CHECK(result == false);
    cc.push(input);
    BOOST_CHECK(cc.size() == 1);
    result = cc.try_pop(output);
    BOOST_CHECK(cc.size() == 0);
    BOOST_CHECK(result == true);
    BOOST_CHECK(output == input);
    result = cc.try_pop(output);
    BOOST_CHECK(result == false);

    cc.push(input);
    BOOST_CHECK(cc.size() == 1);
    cc.wait_and_pop(output);
    BOOST_CHECK(cc.size() == 0);
    BOOST_CHECK(output == input);
}

// Push on queue the given number of times.
void do_push(bites::ConcurrentQueue<int>* cc, int count)
{
    for(int ii=0; ii<count; ++ii){
        cc->push(ii);
    }
}

// Pop from queue the given number of times.
void do_pop(bites::ConcurrentQueue<int>* cc, int count)
{
    for(int ii=0; ii<count; ++ii){
        int output;
        cc->wait_and_pop(output);
    }
}

// Two-thread use of the queue.
BOOST_AUTO_TEST_CASE(test2)
{
    bites::ConcurrentQueue<int> cc;
    const int COUNT = 1000;
    std::thread first (do_push, &cc, COUNT);
    std::thread second (do_pop, &cc, COUNT);
    first.join();
    second.join();
    BOOST_CHECK(cc.size() == 0);
}

// Multi-producer, multi-consumer use of the queue.
BOOST_AUTO_TEST_CASE(test3)
{
    bites::ConcurrentQueue<int> cc;
    const int PRODUCER_COUNT = 32;
    const int CONSUMER_COUNT = 32;
    const int PUSH_COUNT = 128;
    std::queue< std::thread* > producers;
    std::queue< std::thread* > consumers;

    for(int ii=0; ii<PRODUCER_COUNT; ++ii){
        auto thread = new std::thread(do_push, &cc, PUSH_COUNT);
        producers.push(thread);
    }

    for(int ii=0; ii<CONSUMER_COUNT; ++ii){
        auto thread = new std::thread(do_pop, &cc, PUSH_COUNT);
        consumers.push(thread);
    }

    for(int ii=0; ii<PRODUCER_COUNT; ++ii){
        std::thread* thread = producers.front();
        producers.pop();
        thread->join();
        delete thread;
    }

    for(int ii=0; ii<CONSUMER_COUNT; ++ii){
        std::thread* thread = consumers.front();
        consumers.pop();
        thread->join();
        delete thread;
    }

    BOOST_CHECK(cc.size() == 0);
}

BOOST_AUTO_TEST_SUITE_END()
