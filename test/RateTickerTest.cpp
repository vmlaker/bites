// Test of RateTicker class.

#include <vector>
#include <boost/test/unit_test.hpp>
#include "bites.hpp"

BOOST_AUTO_TEST_SUITE(RateTicker_Test)

// Tick a simple ticker.
BOOST_AUTO_TEST_CASE(test1)
{
    std::vector<int> periods = { 1 };
    bites::RateTicker aa (periods);
    BOOST_CHECK(aa.tick() == std::vector<float>({ 1.0 }));
}

// Tick a three-period ticker.
BOOST_AUTO_TEST_CASE(test2)
{
    std::vector<int> periods = { 1, 2, 5 };
    bites::RateTicker aa (periods);
    BOOST_CHECK( aa.tick() == std::vector<float>({ 1, 0.5, 0.2 }) );
}

BOOST_AUTO_TEST_SUITE_END()
