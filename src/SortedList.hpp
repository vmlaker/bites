// Sorted list.

#ifndef __SORTEDLIST_HPP__
#define __SORTEDLIST_HPP__

#include <list>
using namespace std;

template<typename T>
class SortedList
{
public:
    SortedList(const list<T>& = list<T>());
    void add(const T& item);
    unsigned int getCountLT(const T& item) const;
    unsigned int getCountGT(const T& item) const;
    unsigned int removeLT(const T& item);

private:
    list<T> m_data;
};

#endif //__SORTEDLIST_HPP__
