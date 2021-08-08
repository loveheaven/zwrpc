#pragma once

#if defined(__APPLE__)
#include <TargetConditionals.h>
#define OS_MACOSX 1
#elif defined(__linux__)
#define OS_LINUX 1
#elif defined(_WIN32)
#define OS_WIN32 1
#endif

#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
#define BUTIL_CXX11_ENABLED 1
#endif

#if !defined(BUTIL_CXX11_ENABLED)
#define nullptr NULL
#endif

#if !defined(BUTIL_CXX11_ENABLED)
#define BUTIL_DELETE_FUNCTION(decl) decl
#else
#define BUTIL_DELETE_FUNCTION(decl) decl = delete
#endif

// Put this in the private: declarations for a class to be uncopyable.
#define DISALLOW_COPY(TypeName)                         \
    BUTIL_DELETE_FUNCTION(TypeName(const TypeName&))

// Put this in the private: declarations for a class to be unassignable.
#define DISALLOW_ASSIGN(TypeName)                               \
    BUTIL_DELETE_FUNCTION(void operator=(const TypeName&))

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName)                      \
    BUTIL_DELETE_FUNCTION(TypeName(const TypeName&));            \
    BUTIL_DELETE_FUNCTION(void operator=(const TypeName&))