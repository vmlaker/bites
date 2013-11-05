// Test of Config class.

#include "Config.hpp"
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

// Start from empty, set and get.
BOOST_AUTO_TEST_CASE(test1)
{
    Config cc;
    cc["NAME"] = "Bender";
    cc["SURNAME"] = "Rodríguez";
    BOOST_CHECK_EQUAL(cc["NAME"], "Bender");
    BOOST_CHECK_EQUAL(cc["SURNAME"], "Rodríguez");
}

// Read from file and get.
BOOST_AUTO_TEST_CASE(test2)
{
    Config cc("src/simple.cfg");
    BOOST_CHECK_EQUAL(cc["TOON"], "Bugs Bunny");
    BOOST_CHECK_EQUAL(cc["QUOTE"], "The quick brown fox jumped over the lazy dog.");
}

// Read from file containing erroneous line, and get.
BOOST_AUTO_TEST_CASE(test3)
{
    Config cc("src/simple2.cfg");
    BOOST_CHECK_EQUAL(cc["Kingdom"], "Animalia");
    BOOST_CHECK_EQUAL(cc["Genus"], "Python");
}

//Read from file, get, save, load via constructor and load().
BOOST_AUTO_TEST_CASE(test4)
{
    const char* fname1 = "src/simple.cfg";
    Config cc1(fname1);
    const char* fname2 = "src/test4.out";
    cc1.save(fname2);
    Config cc2(fname2);
    BOOST_CHECK_EQUAL(cc2["TOON"], "Bugs Bunny");
    BOOST_CHECK_EQUAL(cc2["QUOTE"], "The quick brown fox jumped over the lazy dog.");
    Config cc3;
    cc3.load(fname2);
    BOOST_CHECK_EQUAL(cc3["TOON"], "Bugs Bunny");
    BOOST_CHECK_EQUAL(cc3["QUOTE"], "The quick brown fox jumped over the lazy dog.");
}