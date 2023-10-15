#ifndef LOG_H
#define LOG_H

#include <iostream>

#define DEBUG_LEVEL_DBG 0
#define DEBUG_LEVEL_ERR 1
#define DEBUG_LEVEL_INFO 2
#define DEBUG_LEVEL_MAX 3

#define DEBUG_LEVEL DEBUG_LEVEL_ERR

inline void LOG_DBG()
{
#if (DEBUG_LEVEL <= DEBUG_LEVEL_DBG)
    std::cout << "." << std::endl;
#endif
}

template<typename Type, typename ...Types>
inline void LOG_DBG(const Type &firstArg, const Types &...args)
{
#if (DEBUG_LEVEL <= DEBUG_LEVEL_DBG)
    std::cout << firstArg;
    LOG_DBG(args...);
#endif
}

inline void LOG_ERR()
{
#if (DEBUG_LEVEL <= DEBUG_LEVEL_ERR)
    std::cout << "." << std::endl;
#endif
}

template<typename Type, typename ...Types>
inline void LOG_ERR(const Type &firstArg, const Types &...args)
{
#if (DEBUG_LEVEL <= DEBUG_LEVEL_ERR)
    std::cout << firstArg;
    LOG_ERR(args...);
#endif
}

inline void LOG_INFO()
{
#if (DEBUG_LEVEL <= DEBUG_LEVEL_INFO)
    std::cout << "." << std::endl;
#endif
}

template<typename Type, typename ...Types>
inline void LOG_INFO(const Type &firstArg, const Types &...args)
{
#if (DEBUG_LEVEL <= DEBUG_LEVEL_INFO)
    std::cout << firstArg;
    LOG_INFO(args...);
#endif
}

#endif
