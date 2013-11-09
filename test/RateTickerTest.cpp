// Test of RateTicker class.

#include <vector>
using namespace std;
#include <boost/test/unit_test.hpp>
#include "RateTicker.hpp"

BOOST_AUTO_TEST_SUITE(RateTicker_Test)

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

BOOST_AUTO_TEST_SUITE_END()
