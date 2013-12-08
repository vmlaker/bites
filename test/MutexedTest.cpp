/**
   Test of Mutexed template class.
*/
#include <boost/test/unit_test.hpp>
#include "bites.hpp"

BOOST_AUTO_TEST_SUITE(Mutexed_Test)

/**
   Continuously sets a mutexed variable.
*/
class Setter : public bites::Thread 
{
public:
    /**
       Initialize the thread object.
       @param  stop_flag  Mutexed flag signalling to stop.
       @param  variable   Mutexed variable to be set.
       @param  value      The string value to set the variable.
    */
    Setter (
        bites::Mutexed <bool>& stop_flag,
        bites::Mutexed <std::string>& variable, 
        const std::string& value
        ):
        m_stop_flag (stop_flag),
        m_variable  (variable),
        m_value     (value) 
        {/* Empty. */}
private:
    bites::Mutexed <bool>& m_stop_flag;
    bites::Mutexed <std::string>& m_variable;
    const std::string m_value;
    /**
       Keep setting the variable until signalled to stop.
    */
    void run()
    {
        while(!m_stop_flag.get()) 
        { 
            m_variable.set (m_value);
        }
    }
};

BOOST_AUTO_TEST_CASE(test1)
{
    bites::Mutexed <bool> stop_flag (false);
    bites::Mutexed <std::string> variable;

    // Create the Setter threads.
    const int THREAD_COUNT = 32;
    std::list <Setter*> setters;
    for(int ii=0; ii<THREAD_COUNT; ++ii)
    {
        auto setter = new Setter (stop_flag, variable, std::to_string(ii));
        setters.push_back(setter);
    }

    // Start the threads.
    for( auto setter : setters ) setter->start();

    // Test the variable for all possible values.
    for(int ii=0; ii<THREAD_COUNT; ++ii){
        while (variable.get() != std::to_string(ii))
        {
            // Do nothing.
        }
    }

    // Signal stop.
    stop_flag.set(true);

    // Join and release.
    for(auto setter : setters){
        setter->join();
        delete setter;
    }

    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
