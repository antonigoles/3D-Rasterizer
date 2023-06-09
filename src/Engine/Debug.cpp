#include <string>
#include <iostream>

#define DEBUG_LEVEL 0

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

namespace Engine 
{
    namespace Debug
    {

        bool DRAW_EDGES_ONLY = false;

        void logln(std::string message, int debug_level = 0) 
        {
            if ( debug_level <= DEBUG_LEVEL ) 
                std::cout << message << "\n";
        }

        void log(std::string message, int debug_level = 0) 
        {
            if ( debug_level <= DEBUG_LEVEL ) 
                std::cout << message;
        }

        void logrich(std::string message, int debug_level = 0) {
            if ( debug_level <= DEBUG_LEVEL ) 
                std::cout << BOLDYELLOW << "[" <<  "Logger" << "]: " << WHITE << message << RESET << "\n";
        }

        void errorrich(std::string message, int debug_level = 0) {
            if ( debug_level <= DEBUG_LEVEL ) 
                std::cout << BOLDRED << "[" <<  "Error" << "]: " << WHITE << message << RESET << "\n";
        }
    }
}