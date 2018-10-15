/*
 * File:   setup/api.h
 * Author: Miles Lacey
 *
 * Created on October 11, 2015, 3:08 PM
 */

#ifndef LS_SETUP_API_H
#define LS_SETUP_API_H

#include "lightsky/setup/Arch.h"
#include "lightsky/setup/Compiler.h"
#include "lightsky/setup/OS.h"



/*
 * Dynamic Library Setup
 */
#if defined(LS_OS_WINDOWS) && defined(LS_SHARED) && defined (LS_COMPILER_MSC)
    #ifdef LS_BUILD_SHARED
        #define LS_API __declspec( dllexport )
    #else
        #define LS_API __declspec( dllimport )
    #endif

#elif defined(LS_SHARED) && defined (LS_COMPILER_GNU)
    #ifdef LS_BUILD_SHARED
        #define LS_API __attribute__((__visibility__("default")))
    #else
        #define LS_API
    #endif

#else
    #define LS_API
#endif



/*
 * Calling Conventions
 */
#if defined(LS_ARCH_X86)
    #if defined(LS_OS_WINDOWS)
        #define LS_C_CALL __stdcall
    #elif defined LS_COMPILER_GNU
        #define LS_C_CALL __attribute__ ((stdcall))
    #endif
#else
    #define LS_C_CALL
#endif



/*
 * Object Inlining and Calling Conventions to be used in performance-sensitive functions
 */
#if defined(LS_COMPILER_MSC) || defined(LS_COMPILER_BORLAND)
    #define LS_INLINE __forceinline

	#if defined(LS_ARCH_X86) && (LS_ARCH_X86 == 32)
		#define LS_FASTCALL __fastcall
    #else
		#define LS_FASTCALL
    #endif

#elif defined (LS_COMPILER_GNU)
    #define LS_INLINE __attribute__((always_inline))

	#if defined (LS_ARCH_X86) && (LS_ARCH_X86 == 32)
			#define LS_FASTCALL __attribute__((fastcall))
    #else
        #define LS_FASTCALL
    #endif

#else
    #define LS_INLINE inline
    #define LS_FASTCALL
#endif



#ifndef LS_IMPERATIVE
    #define LS_IMPERATIVE LS_INLINE LS_FASTCALL
#endif



#endif  /* LS_SETUP_API_H */
