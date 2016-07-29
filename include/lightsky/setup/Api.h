/*
 * File:   setup/api.h
 * Author: Miles Lacey
 *
 * Created on October 11, 2015, 3:08 PM
 */

#ifndef __LS_SETUP_API_H__
#define __LS_SETUP_API_H__

#include "lightsky/setup/OS.h"
#include "lightsky/setup/Arch.h"

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
#if defined (LS_ARCH_X86) && defined (LS_OS_WINDOWS)
#define LS_CALL __stdcall
#else
#define LS_CALL
#endif

#endif  /* __LS_SETUP_API_H__ */
