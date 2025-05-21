#ifndef ERROR_H
#define ERROR_H


#include <iostream>
#include <exception>
#include <string>
#include <execinfo.h>
#include <cstdlib>

/// Using backtrace to print fully exception details.
/// @note (Only works on linux!)
void print_stacktrace();

#endif
