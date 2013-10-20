// Test of Averager class.

#include "Averager.hpp"
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(my_test)
{
    Averager averager(2);

    BOOST_CHECK_EQUAL(averager.add(1.0), 1.0);
    BOOST_CHECK_EQUAL(averager.length(), 1);

    BOOST_CHECK_EQUAL(averager.add(2.0), 1.5);
    BOOST_CHECK_EQUAL(averager.length(), 2);

    BOOST_CHECK_EQUAL(averager.add(3.0), 2.5);
    BOOST_CHECK_EQUAL(averager.length(), 2);
    
    BOOST_REQUIRE(true);
}
