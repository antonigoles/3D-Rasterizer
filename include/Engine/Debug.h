#pragma once

#include <string>

namespace Engine 
{
    namespace Debug
    {
        void logln(std::string message, int debug_level = 0);
        void log(std::string message, int debug_level = 0);
        void logrich(std::string message, int debug_level = 0);
        void errorrich(std::string message, int debug_level = 0);
        extern bool DRAW_EDGES_ONLY;
    }
}