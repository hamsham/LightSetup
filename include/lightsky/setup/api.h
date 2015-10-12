/* 
 * File:   setup/api.h
 * Author: Miles Lacey
 *
 * Created on October 11, 2015, 3:08 PM
 */

#ifndef __LS_SETUP_API_H__
#define	__LS_SETUP_API_H__

#include "lightsky/setup/os.h"
#include "lightsky/setup/arch.h"

/*
 * Dynamic Library Setup
 */
#if defined(LS_OS_WINDOWS) && defined(LS_SHARED)
    #ifdef LS_BUILD_SHARED
        #define LS_API __declspec( dllexport )
    #else
        #define LS_API __declspec( dllimport )
    #endif
#else
    #define LS_API
#endif

/*
 * Calling Conventions
 */
#if defined (LS_ARCH_X86) && defined (LS_OS_WINDOWS)
    #define LS_CALL __stdcall
#else
    #define LS_CALL
#endif

#endif	/* __LS_SETUP_API_H__ */

