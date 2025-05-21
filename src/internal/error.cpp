// Including C++ standard libraries

// Including self libraries
#include "WeaNet/Internal/error.h"

void print_stacktrace() {
    void* array[10];
    size_t size = backtrace(array, 10);
    char** symbols = backtrace_symbols(array, size);

    std::cerr << "Stacke trace:\n";
    for (size_t i =0; i < size; i++) {
        std::cerr << symbols[i] << std::endl;
    }
    free(symbols);
}
