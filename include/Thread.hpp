#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <thread>

namespace bites {

/**
  Allows creating thread "objects"
  similarly to Python's Thread (or Process) class.
  For example, in Python you'd create your class this way:

  @code

  from threading import Thread

  class Foo(Thread):
     def __init__(self):
        super(Foo, self).__init__()
     def run(self):
        print('Hello!')

  bar = Foo()
  bar.start()
  bar.join()

  @endcode

  Using Thread class, the analogous C++ definition is:

  @code

  #include <iostream>
  #include <bites.hpp>

  class Foo : public bites::Thread {
  private:
     void run() { std::cout << "Hello!" << std::endl; }
  };

  int main (int argc, char** argv) {
     bar Foo;
     bar.start();
     bar.join();
  }

  @endcode
 */
class Thread {

public:
    /**
       Deallocate memory for internal thread object.
     */
    ~Thread()
    {
        if (m_thread) 
        {
            delete m_thread;
        }
    }

    /**
       Allocate (and start) internal thread object.
    */
    void start ()
    {
        m_thread = new std::thread(&Thread::run, this);
    }

    /**
      Join internal thread.
    */
    void join ()
    {
        if (m_thread)
        {
            m_thread->join();
        }
    }

private:
    std::thread* m_thread = NULL;

    /**
       Implement this in subclass.
    */
    virtual void run() = 0;
};

}  // namespace sherlock.

#endif  // __THREAD_HPP__
