// Averager.

#include "Averager.hpp"

using namespace std;

// The constructor.
Averager::Averager(const int& max_count) 
    : max_count(max_count > 1 ? max_count : 1),  // Minimum is 1.
      data()
{  /* Empty. */ }


// Add a value, and return current average.
float Averager::add(const float& value){

    // Add new value.
    this->data.push_front(value);
    if(this->data.size() > this->max_count){
        this->data.pop_back();
    }

    // Compute the average.
    float total;
    for(deque<float>::iterator ii = this->data.begin(); ii < this->data.end(); ++ii){
        total += *ii;
    }
    float result = total/this->data.size();
    return result;
}

// Return number of samples.
int Averager::length(){
    return this->data.size();
}
