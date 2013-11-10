// Rate ticker.

#ifndef __RATETICKER_HPP__
#define __RATETICKER_HPP__

#include <vector>
#include <boost/date_time.hpp>
#include "SortedList.hpp"

class RateTicker
{
public:
    RateTicker(const std::vector<float>& periods);
    std::vector<float> tick();
private:
    std::vector<float> m_periods;
    SortedList<boost::posix_time::ptime> m_history;
};

#endif //__RATETICKER_HPP__
