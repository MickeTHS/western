#pragma once

namespace wst {
    #if !defined(NOTRACE)
    void trace_handler(const char *, const char *, int, const char *, ...);
    #ifdef WIN32
    #define TRACE(msg, ...) { wst::trace_handler(__FILE__, __FUNCTION__, __LINE__, msg, __VA_ARGS__); }
    #else //GCC
    #define TRACE(msg, ...) { wst::trace_handler(__FILE__, __FUNCTION__, __LINE__, msg, ##__VA_ARGS__); }
    #endif
    #else
    #define TRACE(msg, ...) { }
    #endif
}