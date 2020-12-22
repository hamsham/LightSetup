/*
 * File:   setup/arch.h
 * Author: Miles Lacey
 *
 * This file contains preprocessor macros detailing information about the
 * currently targeted architecture.
 *
 */

#ifndef LS_SETUP_ARCH_H
#define LS_SETUP_ARCH_H

/*
 * x86/x64 Processor Family
 */
#if defined (_WIN64) || defined (__amd64__) || defined (_M_X64)
    #define LS_ARCH_X86 64
    #define LS_ARCH_X86_VER 6 /* Assuming modern processors */

#elif defined (_WIN32) || defined (__i386__) || defined (_M_IX86_) || defined (__THW_INTEL__)
    #ifndef LS_ARCH_X86
        #define LS_ARCH_X86 32
    #endif

    /*
     * x86 Versioning
     */
    #ifdef LS_COMPILER_GNU
        #if defined (__i686__)
            #define LS_ARCH_X86_VER 686
        #elif defined (__i586__)
            #define LS_ARCH_X86_VER 586
        #elif defined (__i486__)
            #define LS_ARCH_X86_VER 486
        #elif defined (__i386__)
            #define LS_ARCH_X86_VER 386
        #endif
    #elif defined (LS_COMPILER_MSC)
        #define LS_ARCH_X86_VER ((_M_IX86) / 100)
    #else
        #define LS_ARCH_X86_VER 386
    #endif
#endif

/*
 * x86-CPU Features
 */
#ifdef LS_ARCH_X86
    #ifdef __SSE__
        #define LS_X86_SSE
    #endif

    #ifdef __SSE2__
        #define LS_X86_SSE2
    #endif

    #ifdef __SSE3__
        #define LS_X86_SSE3
    #endif

    #ifdef __SSSE3__
        #define LS_X86_SSSE3
    #endif

    #ifdef __SSE4_1__
        #define LS_X86_SSE4_1
    #endif

    #ifdef __SSE4_2__
        #define LS_X86_SSE4_2
    #endif

    #ifdef __AVX__
        #define LS_X86_AVX
    #endif

    #ifdef __AVX2__
        #define LS_X86_AVX2
    #endif

    #ifdef __F16C__
        #define LS_X86_FP16
    #endif

    #ifdef __BMI__
        #define LS_X86_BMI
    #endif

    #ifdef __LZCNT__
        #define LS_X86_LZCNT
    #endif

    #ifdef __POPCNT__
        #define LS_X86_POPCNT
    #endif

    #ifdef __FMA__
        #define LS_X86_FMA
    #endif

#endif

/*
 * Itanium
 */
#if defined (__IA64__) || defined (_M_IA64) || defined (__itanium__)
    #define LS_ARCH_IA64 1
#endif

/*
 * Arm Processors
 */
#if defined (__arm__) || defined (_M_ARM) || defined (__TARGET_ARCH_ARM) || defined(__aarch64__)
    #define LS_ARCH_ARM 1
    #define LS_ARCH_ARM_VER LS_MAX( (__TARGET_ARCH_ARM), (_M_ARM) )

    /*
     * 64-bit ARM
     */
    #if defined(__aarch64__)
        #define LS_ARCH_AARCH64
    #endif

    /*
     * Thumb-Mode
     */
    #if defined (__thumb__) || defined (__TARGET_ARCH_THUMB) || defined (_M_ARMT)
        #define LS_ARCH_ARM_THUMB 1
        #define LS_ARCH_ARM_THUMB_VER LS_MAX( (__TARGET_ARCH_THUMB), (_M_ARMT) )
    #endif
#endif

/*
 * PowerPC
 */
#if defined (__ppc__) || defined (_M_PPC) || defined (_ARCH_PPC)
    #define LS_ARCH_PPC 1
#endif

/*
 * Gaming Consoles
 */
#if defined (__SNC__)
    #define LS_ARCH_PS3 1
#endif

#endif /* LS_SETUP_ARCH_H */
