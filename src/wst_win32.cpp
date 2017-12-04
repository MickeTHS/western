#include "wst_trace.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <Windows.h>

namespace wst {

    #if !defined(NOTRACE)
    struct trlog
    {
        FILE *log_file;
        trlog() { fopen_s(&log_file, "western.log", "w"); }
        ~trlog() { fclose(log_file); }
        static void write_msg(const char *file, const char *func, int line, const char *msg)
        {
            static trlog log;
            fprintf(log.log_file, "%s %s %d %s", file, func, line, msg);
        }
    };


    void trace_handler(const char *file, const char *func, int line, const char *msg, ...)
    {
        static char bf[4096] = { 0 };

        va_list args;
        va_start(args, msg);
        _vsnprintf_s(bf, 4095, msg, args);
        va_end(args);

        bf[4095] = 0;

        OutputDebugString(bf);
        trlog::write_msg(file, func, line, bf);
    }
    #endif
}