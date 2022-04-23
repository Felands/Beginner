#ifndef LOG_H
#define LOG_H

#include <iostream>

//#define DEBUG

inline void LOG_DBG()
{
#ifdef DEBUG
    std::cout << "." << std::endl;
#endif
}

template<typename Type, typename ...Types>
inline void LOG_DBG(const Type &firstArg, const Types &...args)
{
#ifdef DEBUG
    std::cout << firstArg;
    LOG_DBG(args...);
#endif
}

inline void LOG_ERR()
{
    std::cout << "." << std::endl;
}

template<typename Type, typename ...Types>
inline void LOG_ERR(const Type &firstArg, const Types &...args)
{
    std::cout << firstArg;
    LOG_ERR(args...);
}

#endif
