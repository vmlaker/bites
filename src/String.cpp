/**
   String utilities.
*/

// Include standard headers.
#include <sstream>
#include <string>
#include <vector>

// Include application headers.
#include "bites.hpp"

namespace bites {

std::string time2string(
    const std::chrono::time_point<std::chrono::high_resolution_clock>& given_time,
    const std::string& format)
{
    auto tt = std::chrono::system_clock::to_time_t( given_time );
    char buf [64];
    std::strftime( 
        buf, 
        64,
        format.c_str(),
        std::localtime( &tt )
        );
    std::string result (buf);

    // Replace microseconds, if indicated.
    auto loc = result.find ("%f");
    if( loc != std::string::npos )
    {
        auto ms = std::chrono::duration_cast<std::chrono::microseconds> (given_time.time_since_epoch());
        std::stringstream ms_ss;
        ms_ss << std::setfill('0') << std::setw(6) << ms.count() % 1000000;
        std::string ms_str;
        ms_ss >> ms_str;
        while( ( loc = result.find("%f") ) != std::string::npos )
        {
            result.replace (loc, 2, ms_str);
        }
    }

    return result;
}

std::vector<std::string> time2levels( 
    const std::chrono::time_point<std::chrono::high_resolution_clock>& given_time )
{
    auto tstring = time2string( given_time, "%Y %m %d %H %M" );
    std::string segment;
    std::stringstream ss (tstring);
    std::vector<std::string> result;
    while (ss >> segment){
        result.push_back(segment);
    }
    return result;
}

boost::filesystem::path time2dir(
    const std::chrono::time_point <std::chrono::high_resolution_clock>& given_time )
{
    boost::filesystem::path result;
    for (auto field : time2levels(given_time))
    {
        result /= boost::filesystem::path(field);
    }
    return result;
}

}  // namespace bites.
