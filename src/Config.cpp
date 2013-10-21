// Config.

#include "Config.hpp"
#include <fstream>
using namespace std;

Config::Config(const string& fname)
    : m_fname(fname),
      m_data()
{
    if(!fname.empty()){
        this->load();
    }
}

void Config::load(const string& fname){
    if(!fname.empty()){
        this->loadFromFile(fname);
    }else{
        this->loadFromFile(this->m_fname);
    }
}

void Config::loadFromFile(const string& fname){
    ofstream ifile(fname.c_str());
    
    // TODO: Implement load.

    ifile.close();
}
