// Copyright 2022 by dbj@dbj.org
#ifndef DBJ_DLL_WALL_OF_MACROS_
#define DBJ_DLL_WALL_OF_MACROS_

#include <ctype.h>
#include <stddef.h>

#define dbj_dll_MAJOR  0
#define dbj_dll_MINOR  1
#define dbj_dll_PATCH  0

#define  dbj_dll_VERSION  dbj_dll_STRINGIFY(dbj_dll_MAJOR) "." dbj_dll_STRINGIFY(dbj_dll_MINOR) "." dbj_dll_STRINGIFY(dbj_dll_PATCH)

#if 0
#ifdef    dbj_dll_FEATURE_RTTI
# define  dbj_dll__cpp_rtti  dbj_dll_FEATURE_RTTI
#elif defined(__cpp_rtti)
# define  dbj_dll__cpp_rtti  __cpp_rtti
#elif defined(__GXX_RTTI) || defined (_CPPRTTI)
# define  dbj_dll__cpp_rtti  1
#else
# define  dbj_dll__cpp_rtti  0
#endif
#endif // 0

// Stringify:

#define dbj_dll_STRINGIFY(  x )  dbj_dll_STRINGIFY_( x )
#define dbj_dll_STRINGIFY_( x )  #x

// Compiler warning suppression:

#if defined (__clang__)
# pragma clang diagnostic ignored "-Waggregate-return"
# pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunused-comparison"
#elif defined (__GNUC__)
# pragma GCC   diagnostic ignored "-Waggregate-return"
# pragma GCC   diagnostic push
#endif

// Suppress shadow and unused-value warning for sections:

#if defined (__clang__)
# define dbj_dll_SUPPRESS_WSHADOW    _Pragma( "clang diagnostic push" ) \
                                  _Pragma( "clang diagnostic ignored \"-Wshadow\"" )
# define dbj_dll_SUPPRESS_WUNUSED    _Pragma( "clang diagnostic push" ) \
                                  _Pragma( "clang diagnostic ignored \"-Wunused-value\"" )
# define dbj_dll_RESTORE_WARNINGS    _Pragma( "clang diagnostic pop"  )

#elif defined (__GNUC__)
# define dbj_dll_SUPPRESS_WSHADOW    _Pragma( "GCC diagnostic push" ) \
                                  _Pragma( "GCC diagnostic ignored \"-Wshadow\"" )
# define dbj_dll_SUPPRESS_WUNUSED    _Pragma( "GCC diagnostic push" ) \
                                  _Pragma( "GCC diagnostic ignored \"-Wunused-value\"" )
# define dbj_dll_RESTORE_WARNINGS    _Pragma( "GCC diagnostic pop"  )
#else
# define dbj_dll_SUPPRESS_WSHADOW    /*empty*/
# define dbj_dll_SUPPRESS_WUNUSED    /*empty*/
# define dbj_dll_RESTORE_WARNINGS    /*empty*/
#endif

// C++ language version detection (C++20 is speculative):

#ifndef   dbj_dll_CPLUSPLUS
# if defined(_MSVC_LANG ) && !defined(__clang__)
#  define dbj_dll_CPLUSPLUS  (_MSC_VER == 1900 ? 201103L : _MSVC_LANG )
# else
#  define dbj_dll_CPLUSPLUS  __cplusplus
# endif
#endif

#define dbj_dll_CPP98_OR_GREATER  ( dbj_dll_CPLUSPLUS >= 199711L )
#define dbj_dll_CPP11_OR_GREATER  ( dbj_dll_CPLUSPLUS >= 201103L )
#define dbj_dll_CPP14_OR_GREATER  ( dbj_dll_CPLUSPLUS >= 201402L )
#define dbj_dll_CPP17_OR_GREATER  ( dbj_dll_CPLUSPLUS >= 201703L )
#define dbj_dll_CPP20_OR_GREATER  ( dbj_dll_CPLUSPLUS >= 202000L )


#endif // DBJ_DLL_WALL_OF_MACROS_
