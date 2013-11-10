// Config.

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "Config.hpp"

Config::Config(const std::string& fname)
    : m_data()
{
    if(!fname.empty()){
        this->load(fname);
    }
}

void Config::load(const std::string& fname)
{
    // Iterate through lines in the file.
    std::ifstream infile(fname.c_str());
    std::string line;
    int count = 0;  // Keep a running count of lines.
    while(getline(infile, line)){
        count += 1;
        boost::algorithm::trim(line);

        // Skip empty lines and comment lines.
        if(line.empty()){
            continue;
        }
        if(line[0] == '#'){
            continue;
        }

        // Extract the key/value pair.
        std::istringstream iss(line);        
        std::string key;
        iss >> key;
        std::string value;
        getline(iss, value);
        boost::algorithm::trim(value);

        if(value.empty()){
            std::cout << "Error line " << count;
            std::cout << " file " << fname << std::endl;
            continue;
        }
        m_data[key] = value;  // Add to internal container.
    }
    infile.close();
}

void Config::save(const std::string& fname) const
{
    std::ofstream outfile(fname.c_str());
    outfile << *this;
    outfile.close();
}

std::string& Config::operator[](const std::string& key)
{
    return m_data[key];
}

std::ostream& operator<<(std::ostream& out, const Config& config)
{
    for(auto ii=config.m_data.begin(); ii!=config.m_data.end(); ++ii)
    {
        out << ii->first << " " << ii->second << std::endl;
    }
}
