/*!
  Test of Averager class.
*/
#include <boost/test/unit_test.hpp>
#include "bites.hpp"

BOOST_AUTO_TEST_SUITE(Averager_Test)

BOOST_AUTO_TEST_CASE(my_test)
{
    bites::Averager averager(2);

    BOOST_CHECK_EQUAL(averager.add(1.0), 1.0);
    BOOST_CHECK_EQUAL(averager.length(), 1);

    BOOST_CHECK_EQUAL(averager.add(2.0), 1.5);
    BOOST_CHECK_EQUAL(averager.length(), 2);

    BOOST_CHECK_EQUAL(averager.add(3.0), 2.5);
    BOOST_CHECK_EQUAL(averager.length(), 2);
}

BOOST_AUTO_TEST_SUITE_END()
