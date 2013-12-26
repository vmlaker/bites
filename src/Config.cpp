/**
   Config class implementation.
*/

// Include standard headers. 
#include <iostream>
#include <fstream>
#include <sstream>

// Include 3rd-party headers.
#include <boost/algorithm/string.hpp>

// Include application headers.
#include "bites.hpp"

namespace bites {

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
        boost::algorithm::trim_left(line);

        // Skip empty lines and comment lines.
        if(line.empty()){
            continue;
        }
        if(line[0] == '#'){
            continue;
        }

        // Process continuation on next line(s).
        while(line.back() == '\\'){
            std::string line2;
            getline(infile, line2);

            count += 1;
            boost::algorithm::trim_left(line2);

            // Skip empty comment lines.
            if(line2[0] == '#'){
                continue;
            }
            line.erase(line.length() - 1);
            line += line2;
        }
        
        boost::algorithm::trim_right(line);

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
    int count = 0;
    for(auto ii : config.m_data)
    {
        out << ii.first << " " << ii.second;
        if(++count < config.m_data.size())
        {
            out << std::endl;
        }
    }
}

std::vector<std::string> Config::keys()
{
    std::vector<std::string> result;
    for(auto keyval: m_data)
    {
        result.push_back(keyval.first);
    }
    return result;
}

}  // namespace bites.
