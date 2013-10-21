// Config.

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <string>
#include <map>
using namespace std;

class Config{

public:
    Config(const string& fname);
    void load(const string& fname="");
    void save(const string& fname="") const;
    string& operator[](const string& key);
    const string& operator[](const string& key) const;
    friend ostream& operator<<(ostream& out, const Config& config);

private:
    void loadFromFile(const string& fname);
    void safeToFile(const string& fname) const;
    
    string m_fname;
    map<string, string> m_data;
    
};

#endif //__CONFIG_HPP__
