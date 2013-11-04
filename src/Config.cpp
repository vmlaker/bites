// Config.

#include "Config.hpp"

#include <boost/algorithm/string.hpp>
using namespace boost::algorithm;

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Config::Config(const string& fname)
    : m_data()
{
    if(!fname.empty()){
        this->load(fname);
    }
}

void Config::load(const string& fname){
    ifstream infile(fname.c_str());
    int count = 0;
    string line;

    while(getline(infile, line)){
        count += 1;
        trim(line);
        if(line.empty()){
            continue;
        }
        if(line[0] == '#'){
            continue;
        }

        // Extract the key/value pair.
        istringstream iss(line);        
        string key;
        iss >> key;
        string value;
        getline(iss, value);
        trim(value);

        if(value.empty()){
            cout << "Error line " << count << " file " << fname << endl;
            continue;
        }
        m_data[key] = value;
    }

    infile.close();
}

void Config::save(const string& fname) const{
    ofstream outfile(fname.c_str());
    outfile << *this;
}

string& Config::operator[](const string& key){
    return m_data[key];
}

const string& Config::operator[](const string& key) const{
    //return m_data[key];
}

ostream& operator<<(ostream& out, const Config& config){
    for(Config::DataType::const_iterator ii=config.m_data.begin(); 
        ii!=config.m_data.end(); ++ii)
    {
        out << ii->first << " " << ii->second << endl;
    }
}
