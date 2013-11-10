// Averager.

#ifndef __AVERAGER_HPP__
#define __AVERAGER_HPP__

#include <deque>

class Averager{
public:

    // The constructor.
    Averager(const int& max_count);

    // Add a value, and return current average.
    float add(const float& value);

    // Return number of samples.
    int length();

private:
    const int max_count;
    std::deque<float> data;
};

#endif //__AVERAGER_HPP__
