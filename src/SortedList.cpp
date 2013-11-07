// Sorted list.

#include <algorithm>
#include <iterator>
using namespace std;
#include "SortedList.hpp"

// Initialize the object with a copy of the donor list, sorted.
template<typename T>
SortedList<T>::SortedList(const list<T>& donor)
    : m_data(donor)
{
    m_data.sort();
}

// Add item to the list while maintaining sorted order.
template<typename T>
void SortedList<T>::add(const T& item)
{
    m_data.push_back(item);
    m_data.sort();
}

// Return number of elements less than *item*.
template<typename T>
unsigned int SortedList<T>::getCountLT(const T& item) const
{
    auto lower = lower_bound(m_data.begin(), m_data.end(), item);
    return distance(m_data.begin(), lower);
}

// Return number of elements greater than *item*.
template<typename T>
unsigned int SortedList<T>::getCountGT(const T& item) const
{
    auto upper = lower_bound(m_data.begin(), m_data.end(), item);
    return distance(++upper, m_data.end());
}

// Trim off any elements less than *item*, return number of elements trimmed.
template<typename T>
unsigned int SortedList<T>::removeLT(const T& item)
{
    auto lower = lower_bound(m_data.begin(), m_data.end(), item);
    unsigned int count = distance(m_data.begin(), lower);
    m_data.erase(m_data.begin(), lower);
    return count;
}

// Instantiate templates.
template class SortedList<int>;
template class SortedList<float>;
#include <boost/date_time.hpp>
template class SortedList<boost::posix_time::ptime>;
