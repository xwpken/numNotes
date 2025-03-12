#include "map_ex.hpp"


bool AddWord(std::map<std::string, int>& dict, const std::string& keys)
{
    auto it = dict.find(keys);

    bool state = false;

    if (it == dict.end())
    {
        dict[keys] = keys.size();
        state = true;
    }

    return state;

}