// Test of RateTicker class.

#include "RateTicker.hpp"
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <vector>
using namespace std;

// Tick a simple ticker.
BOOST_AUTO_TEST_CASE(test1)
{
    vector<float> periods = { 1 };
    RateTicker aa (periods);
    BOOST_CHECK(aa.tick() == periods);
}

// Tick a three-period ticker.
BOOST_AUTO_TEST_CASE(test2)
{
    vector<float> periods = { 1, 2, 5 };
    RateTicker aa (periods);
    BOOST_CHECK( aa.tick() == vector<float>({ 1, 0.5, 0.2 }) );
}
