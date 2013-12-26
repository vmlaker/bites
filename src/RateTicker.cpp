/**
   RateTicker class implementation.
*/

#include <boost/date_time.hpp>
#include "bites.hpp"

namespace bites {

// Initialize the object with a vector of time periods in seconds.
// For example, use (60, 300, 900) to track rates at 1, 5 and 15 minute
// periods (like when reporting system load.)
RateTicker::RateTicker(const std::vector<float>& periods)
    : m_periods(periods),
      m_history()
{
    /* Empty. */
}

// Tick the ticker. 
// Return a vector of values corresponding to periods given in initializer, 
// each value representing the rate of ticks (number of ticks per second)
// during that period.
std::vector<float> RateTicker::tick()
{
    auto now = boost::posix_time::microsec_clock::universal_time();
    m_history.add(now);

    // Compute timestamps, one for each period,
    // representing the beginning of that period (i.e. since now.)
    std::vector<boost::posix_time::ptime> tstamps (m_periods.size());
    for(int ii=0; ii<tstamps.size(); ++ii){
        auto period = m_periods[ii];
        auto duration = boost::posix_time::seconds(period);
        tstamps[ii] = now - duration;
    }

    // Trim off any tick values older than the earliest timestamp.
    auto iter = min_element(tstamps.begin(), tstamps.end());
    m_history.removeLT(*iter);

    // Create a list of counts, one for each period and
    // representing the number of ticks in that period.
    std::vector <unsigned int> counts (m_periods.size());
    for(int ii=0; ii<counts.size(); ++ii){
        auto tstamp = tstamps[ii];
        counts[ii] = m_history.getCountGT(tstamp) + 1;
    }

    // Compute a list of rates for the periods.
    std::vector <float> rates (m_periods.size());
    for(int ii=0; ii<counts.size(); ++ii){
        rates[ii] = counts[ii] / m_periods[ii];
    }
    return rates;
}

}  // namespace bites.
