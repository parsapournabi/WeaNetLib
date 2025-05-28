#ifndef ERROR_H
#define ERROR_H


#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#ifdef UNIX
    #include <execinfo.h>
#endif

/// Using backtrace to print fully exception details.
/// @note (Only works on linux!)
//void print_stacktrace();

#endif
