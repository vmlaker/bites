/**
   Tests of "string related" functions.
*/
#include <chrono>
#include <boost/test/unit_test.hpp>
#include "bites.hpp"

BOOST_AUTO_TEST_SUITE(String_Test)

/**
   Test time2levels() function.
*/
BOOST_AUTO_TEST_CASE(test1)
{
    auto now = std::chrono::system_clock::now();
    auto result = bites::time2levels (now);
    BOOST_CHECK_EQUAL( result.size(), 5 );

    auto tt = std::chrono::system_clock::to_time_t (now);
    tm* tmtime = localtime(&tt);
    BOOST_CHECK( atoi(result[0].c_str()) == tmtime->tm_year+1900 );
    BOOST_CHECK( atoi(result[1].c_str()) == tmtime->tm_mon+1 );
    BOOST_CHECK( atoi(result[2].c_str()) == tmtime->tm_mday );
    BOOST_CHECK( atoi(result[3].c_str()) == tmtime->tm_hour );
    BOOST_CHECK( atoi(result[4].c_str()) == tmtime->tm_min );
}

/**
   Test time2dir() function.
*/
BOOST_AUTO_TEST_CASE(test2)
{
    auto now = std::chrono::system_clock::now();
    auto result = bites::time2dir( now );
    result = boost::filesystem::path("test") / result;

    boost::filesystem::create_directories (result);
    BOOST_CHECK_EQUAL (true, boost::filesystem::is_directory (result));
    BOOST_CHECK_EQUAL (true, boost::filesystem::exists (result));

    boost::filesystem::remove (result);
    BOOST_CHECK_EQUAL (false, boost::filesystem::is_directory (result));
    BOOST_CHECK_EQUAL (false, boost::filesystem::exists (result));
}

BOOST_AUTO_TEST_SUITE_END()
