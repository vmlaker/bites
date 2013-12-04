// Test of SortedList class.

#include <boost/test/unit_test.hpp>
#include "SortedList.hpp"

BOOST_AUTO_TEST_SUITE(SortedList_Test)

// Start from empty.
BOOST_AUTO_TEST_CASE(test1)
{
    bites::SortedList<int> aa;
    for(int ii=0; ii<10; ++ii){
        aa.add(ii);
    }
    BOOST_CHECK_EQUAL(aa.getCountLT(5), 5);
    BOOST_CHECK_EQUAL(aa.getCountGT(5), 4);
    BOOST_CHECK_EQUAL(aa.removeLT(5), 5);
    BOOST_CHECK_EQUAL(aa.getCountLT(5), 0);
}

// Construct from list.
BOOST_AUTO_TEST_CASE(test2)
{
    std::list<int> donor;
    for(int ii=0; ii<10; ++ii){
        donor.push_back(ii);
    }
    bites::SortedList<int> aa(donor);
    BOOST_CHECK_EQUAL(aa.getCountLT(5), 5);
    BOOST_CHECK_EQUAL(aa.getCountGT(5), 4);
    BOOST_CHECK_EQUAL(aa.removeLT(5), 5);
    BOOST_CHECK_EQUAL(aa.getCountLT(5), 0);
}

BOOST_AUTO_TEST_SUITE_END()
