/*!  
  The Config class implements a micro config settings utility,
  a loadable, saveable, one-line-per-entry config class.
  It just wraps a lookup table with a configuration file
  input/output, and a stream output.

  \code

    Config config1("myapp.conf");

    // All configured values are strings.
    string name = config["nickname"];
    std::cout << "The name is " << name << "." << std::endl;

    int width( config1["WIDTH"] );
   
    // Dump the whole configuration to standard out.
    std::cout << config1 << std::endl;

   \endcode
                                                        
  A configuration file <code>myapp.conf</code> may look like:

  \code

    # Set the window dimensions.
    WIDTH  1920
    HEIGHT 1080

    # Set user and group.
    user      admin
    nickname  The Big Cheese

  \endcode
*/

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <string>
#include <map>

class Config
{
public:
    //!  Create config object, optionally load from file.
    //!  \param fname name of existing file.
    Config(const std::string& fname="");

    //!  Load config contents from file.
    //!  \param fname name of input file.
    void load(const std::string& fname);

    //!  Save config contents to file.
    //!  \param fname name of output file.
    void save(const std::string& fname) const;
    
    //!  Access configuration setting.
    //!  \param key configuration setting to access for read/write.
    std::string& operator[](const std::string& key);

    //!  Dump configuration to stream.
    //!  \param out output destination stream.
    //!  \param config the configuration whose contents are dumped.
    //!
    friend std::ostream& operator<<(std::ostream& out, const Config& config);
    
    //!  Return all keys (names of settings) present in the configuration.
    //!  \returns a vector of strings.
    std::vector<std::string> keys();

private:
    //!  Keep data in a lookup container.
    typedef std::map<std::string, std::string> DataType;
    DataType m_data;
};

#endif //__CONFIG_HPP__
