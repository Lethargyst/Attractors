#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include <iostream>
#include "Json/json.hpp" 

using json = nlohmann::json;

class Config 
{
public:
    static Config& Instance();

private:
    Config() = delete;
    ~Config() = delete;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
};

extern Config& global;

#endif