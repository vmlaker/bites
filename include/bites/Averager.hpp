#ifndef BITES_AVERAGER_HPP_INCLUDED
#define BITES_AVERAGER_HPP_INCLUDED

#include <deque>

namespace bites {

/*!
  Keeps a running average with limited history.
*/
class Averager{
public:

    /*!
      The constructor initializes the averager with 
      maximum number of (latest) samples to keep.
    */
    Averager(const int& max_count);

    /*!
      Add a value, and return current average.
    */
    float add(const float& value);

    /*!
      Return number of samples.
    */
    int length();

private:
    const int max_count;
    std::deque<float> data;
};

}  // namespace bites.

#endif  // BITES_AVERAGER_HPP_INCLUDED
