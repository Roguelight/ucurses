#include <command/Display.hpp>


namespace ucurses { namespace command {

    Map::Map()
    {
        tips.reserve(8);
    }

    void Map::Add(std::string keyID, std::string funcID)
    {
        tips.push_back(commandmap(keyID, funcID));
    }
}}
