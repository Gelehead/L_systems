/***************************************************************
 * Helper class for debugging 
 **************************************************************/
#ifndef HELPER_H
#define HELPER_H

#include <cstdio>
#include <cstdint>

namespace grammar
{
    class Logger 
    {
    public:
        static void info(const char* msg) { std::printf("[INFO] %s\n", msg); }
        static void warning(const char* msg) { std::printf("[WARNING] %s\n", msg); }
        static void error(const char* msg) { std::printf("[ERROR] %s\n", msg); }
    };
}

#endif // HELPER_H