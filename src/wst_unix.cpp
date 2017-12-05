#include "wst_trace.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

namespace wst {

    void log_handler(const char *msg, ...)
    {
        static char bf[4096] = { 0 };

        va_list args;
        va_start(args, msg);
        sprintf(bf, msg, args);
        va_end(args);

        printf("%s", bf);

        bf[4095] = 0;
    }

    #if !defined(NOTRACE)
    struct trlog
    {
        
    };


    void trace_handler(const char *file, const char *func, int line, const char *msg, ...)
    {
        static char bf[4096] = { 0 };

        va_list args;
        va_start(args, msg);
        sprintf(bf, msg, args);
        va_end(args);

        printf("%s", bf);

        bf[4095] = 0;
    }
    #endif
}