// Config.

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <string>
#include <map>

class Config
{
public:
    Config(const std::string& fname="");
    void load(const std::string& fname);
    void save(const std::string& fname) const;
    std::string& operator[](const std::string& key);
    friend std::ostream& operator<<(std::ostream& out, const Config& config);

    typedef std::map<std::string, std::string> DataType;

private:
    DataType m_data;
};

#endif //__CONFIG_HPP__
