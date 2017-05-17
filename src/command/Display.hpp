/*
 *
 *
 */

#pragma once
#include <vector>
#include <string>

namespace ucurses { namespace command {

    using commandmap = std::pair<std::string, std::string>;

    struct Map
    {
        Map();
        std::vector<commandmap> tips;

        void Add(std::string keyID, std::string funcID);
    };

}}
