#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <chrono>  
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

/**
   Various "string" related functions.
   Conversions from Date/Time to filesystem paths.
*/

namespace bites {

/**
   Given the time point, 
   return a vector of directory levels (as strings).
   
   For example, given "2013-09-08 13:01:44",
   return {'2013', '09', '08', '13', '01'}.
*/
std::vector<std::string> time2levels( 
    const std::chrono::time_point <std::chrono::high_resolution_clock>&);

/**
   Given the time point,
   return a filesystem path assembled from time2levels().
*/
boost::filesystem::path time2dir(
    const std::chrono::time_point <std::chrono::high_resolution_clock>&);

}  // namespace bites.

#endif //__STRING_HPP__
