// Sorted list.

#ifndef __SORTEDLIST_HPP__
#define __SORTEDLIST_HPP__

#include <list>

template<typename T>
class SortedList
{
public:

    // Initialize the object with a copy of the donor list, sorted.
    SortedList(const std::list<T>& donor = std::list<T>())
        : m_data(donor)
    {
        m_data.sort();
    }

    // Add item to the list while maintaining sorted order.
    void add(const T& item)
    {
        m_data.push_back(item);
        m_data.sort();
    }

    // Return number of elements less than *item*.
    unsigned int getCountLT(const T& item) const
    {
        auto lower = lower_bound(m_data.begin(), m_data.end(), item);
        return distance(m_data.begin(), lower);
    }

    // Return number of elements greater than *item*.
    unsigned int getCountGT(const T& item) const
    {
        auto upper = lower_bound(m_data.begin(), m_data.end(), item);
        return distance(++upper, m_data.end());
    }

    // Trim off any elements less than *item*, return number of elements trimmed.
    unsigned int removeLT(const T& item)
    {
        auto lower = lower_bound(m_data.begin(), m_data.end(), item);
        unsigned int count = distance(m_data.begin(), lower);
        m_data.erase(m_data.begin(), lower);
        return count;
    }

private:
    std::list<T> m_data;
};

#endif //__SORTEDLIST_HPP__
