// Rate ticker.

#ifndef __RATETICKER_HPP__
#define __RATETICKER_HPP__

#include <vector>
using namespace std;
#include <boost/date_time.hpp>
#include "SortedList.hpp"

class RateTicker
{
public:
    RateTicker(const vector<float>& periods);
    vector<float> tick();
private:
    vector<float> m_periods;
    SortedList<boost::posix_time::ptime> m_history;
};

#endif //__RATETICKER_HPP__
