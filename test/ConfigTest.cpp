// Test of Config class.

#include <set>
#include <boost/test/unit_test.hpp>
#include "Config.hpp"

BOOST_AUTO_TEST_SUITE(Config_Test)

// Start from empty, set and get.
BOOST_AUTO_TEST_CASE(test1)
{
    bites::Config cc;
    cc["NAME"] = "Bender";
    cc["SURNAME"] = "Rodríguez";

    std::set<std::string> known = { "NAME", "SURNAME" };
    for(auto key : cc.keys())
    {
        BOOST_CHECK( known.find(key) != known.end() );
    }

    BOOST_CHECK_EQUAL(cc["NAME"], "Bender");
    BOOST_CHECK_EQUAL(cc["SURNAME"], "Rodríguez");
}

// Read from file and get.
BOOST_AUTO_TEST_CASE(test2)
{
    bites::Config cc("test/simple.cfg");

    std::set<std::string> known = { 
        "TOON", "QUOTE", "width", "height", "item_weight" };
    for(auto key : cc.keys())
    {
        BOOST_CHECK( known.find(key) != known.end() );
    }

    BOOST_CHECK_EQUAL(cc["TOON"], "Bugs Bunny");
    BOOST_CHECK_EQUAL(cc["QUOTE"], "The quick brown fox jumped over the lazy dog.");
    
    auto width = cc["width"];  // Setting "width" is a string;
    BOOST_CHECK_EQUAL(width, std::string("640"));

    // Extract integer value from "1923 lbs (and change.)"
    std::string item_weight(cc["item_weight"]);  // Copy the string.
    int pounds;
    std::stringstream(item_weight) >> pounds;
    BOOST_CHECK_EQUAL(pounds, 1923);
}

// Read from file containing erroneous line, and get.
BOOST_AUTO_TEST_CASE(test3)
{
    bites::Config cc("test/simple2.cfg");
    BOOST_CHECK_EQUAL(cc["Kingdom"], "Animalia");
    BOOST_CHECK_EQUAL(cc["Genus"], "Python");
}

// Read from file, get, save, load via constructor and load().
BOOST_AUTO_TEST_CASE(test4)
{
    const char* fname1 = "test/simple.cfg";
    bites::Config cc1(fname1);
    const char* fname2 = "test/test4.out";
    cc1.save(fname2);
    bites::Config cc2(fname2);
    BOOST_CHECK_EQUAL(cc2["TOON"], "Bugs Bunny");
    BOOST_CHECK_EQUAL(cc2["QUOTE"], "The quick brown fox jumped over the lazy dog.");
    bites::Config cc3;
    cc3.load(fname2);
    BOOST_CHECK_EQUAL(cc3["TOON"], "Bugs Bunny");
    BOOST_CHECK_EQUAL(cc3["QUOTE"], "The quick brown fox jumped over the lazy dog.");
}

// Multi-line settings.
BOOST_AUTO_TEST_CASE(test5)
{
    bites::Config cc("test/simple3.cfg");
    BOOST_CHECK_EQUAL(cc["key2"], "val21");
    BOOST_CHECK_EQUAL(cc["key3"], "val31");
    BOOST_CHECK_EQUAL(cc["key4"], "val41 val42");
    BOOST_CHECK_EQUAL(cc["key5"], "val51 val52");
    BOOST_CHECK_EQUAL(cc["key6"], "val61 val62");
    BOOST_CHECK_EQUAL(cc["key7"], "val71 val72");
}

BOOST_AUTO_TEST_SUITE_END()
