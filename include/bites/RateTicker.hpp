#ifndef BITES_RATETICKER_HPP_INCLUDED
#define BITES_RATETICKER_HPP_INCLUDED

#include <vector>
#include <boost/date_time.hpp>
#include "SortedList.hpp"

namespace bites {

/*!
  Continuous computation of rates of ticking.
 */
class RateTicker
{
public:
    /*!
      Initialize the object with a tuple of time periods in seconds. 
      For example, use (60, 300, 900) to track rates at 1, 5 and 15 minute 
      periods (like when reporting system load.)
    */
    RateTicker(const std::vector<int>& periods);

    /*!
      Tick the ticker. 
      Return a tuple of values corresponding to periods given
      in initializer, each value representing the rate of ticks 
      (number of ticks per second) during that period.
    */
    std::vector<float> tick();
private:
    std::vector<int> m_periods;
    SortedList<boost::posix_time::ptime> m_history;
};

}  // namespace bites.

#endif  // BITES_RATETICKER_HPP_INCLUDED
