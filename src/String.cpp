#include <sstream>
#include <string>
#include <vector>
#include "String.hpp"

namespace bites {

std::vector<std::string> time2levels( 
    const std::chrono::time_point<std::chrono::high_resolution_clock>& given_time )
{
    auto tt = std::chrono::system_clock::to_time_t( given_time );
    char buf [64];
    std::strftime( 
        buf, 
        64,
        "%Y %m %d %H %M",
        std::localtime( &tt )
        );
    std::string segment;
    std::stringstream ss (buf);
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
