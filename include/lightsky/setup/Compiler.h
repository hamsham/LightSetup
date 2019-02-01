/*
 * File:   setup/compiler.h
 * Author: Miles Lacey
 *
 * This file contains preprocessor macros detailing information about the
 * current compiler.
 *
 */

#ifndef LS_SETUP_COMPILER_H
#define LS_SETUP_COMPILER_H



/*
 * Ensure C++11 Support
 */
#if !defined (__GXX_EXPERIMENTAL_CXX0X__) \
    && !(defined (_MSC_VER) && (_MSC_VER >= 1900)) \
    && !(__cplusplus >= 201103L)
    #error "A C++11-compliant compiler is required to build LightSky."
#endif



/*
 * Microsoft Visual C++ compiler
 */
#if defined (_MSC_VER)
    #define LS_COMPILER_MSC _MSC_VER
#endif



/*
 * MinGW Compiler
 */
#if defined(__MINGW32__) || defined(__MINGW_64__)
    #define LS_COMPILER_MINGW
#endif



#if defined(__GNUC__) || defined(__GNUG__) || defined(__MINGW32__) || defined(__MINGW_64__)
    #define LS_COMPILER_GNU __GNUC__

    #if defined(__clang__)
        #define LS_COMPILER_CLANG __clang__
        #define LS_COMPILER_CLANG_MAJ __clang_major__
        #define LS_COMPILER_CLANG_MIN __clang_minor__
    #else
        #define LS_COMPILER_GCC __GNUC__
        #define LS_COMPILER_GCC_MAJ __GNUC_MINOR__
        #define LS_COMPILER_GCC_MIN __GNUC_PATCHLEVEL__
    #endif
#endif



/*
 * Intel Compiler
 */
#if defined (__INTEL_COMPILER)
    #define LS_COMPILER_INTEL __INTEL_COMPILER
#endif



/*
 * Borland
 */
#if defined (__BORLANDC__) || defined (__CODEGEARC__)
    #define LS_COMPILER_BORLAND LS_MAX( (__BORLANDC__), (__CODEGEARC__) )
#endif



/*
 * ARM Compiler
 */
#if defined (__CC_ARM)
    #define LS_COMPILER_ARM __ARMCC_VERSION
#endif



/*
 * IBM Compiler
 */
#if defined (__IBMCPP__)
    #ifdef(__COMPILER_VER__)
        /* IBM z/OS Compiler */
        #define LS_COMPILER_IBM 0
        #define LS_COMPILER_ZOS __IBMCPP__
    #else
        /* IBM XL Compiler */
        #define LS_COMPILER_IBM 1
        #define LS_COMPILER_XL __IBMCPP__
    #endif
#endif



/*
 * Sony's SNC
 */
#if defined (__SNC__)
    #define LS_COMPILER_SN __SNC__
#endif



#endif /* LS_SETUP_COMPILER_H */
