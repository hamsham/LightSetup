
#ifndef LS_SETUP_CPU_H
#define LS_SETUP_CPU_H

#include <cstdint>

#include "lightsky/setup/Api.h"
#include "lightsky/setup/Arch.h"
#include "lightsky/setup/Compiler.h"
#include "lightsky/setup/OS.h"



/*-----------------------------------------------------------------------------
 * CPU-related functions & accessibilities
-----------------------------------------------------------------------------*/
namespace ls
{
namespace setup
{

/**
 * @brief Read the CPU performance/cycle counter.
 *
 * On X86 platforms, this returns the value of the "rdtsc" instruction.
 *
 * ARMv8 platforms will retrieve the value of the "CNTFRQ" register, which
 * uses the active OS's virtual timer.
 *
 * Non-x86 and non-ARM Linux platforms will use the nanosecond timer from
 * clock_gettimeofday().
 *
 * Non-x86 and non-ARM POSIX-2001 platforms will use the nanosecond timer
 * from gettimeofday().
 *
 * All other platforms will return the time since epoch of a
 * std::chrono::high_precision_timer.
 *
 * @return the active CPU's performance counter.
 */
inline int64_t cpu_read_ticks() noexcept;

/**
 * @brief Yield the current thread, using the CPU's native pause instructions.
 *
 * @note This function is implemented with "_mm_pause()" on x86 and
 * "__yield()" on ARMv8. For other *Nix systems this function will use either
 * "clock_nanosleep()" or "nanosleep()". Finally, all other implementations
 * have a fallback to std::this_thread::yield().
 */
inline void cpu_yield() noexcept;

} // setup namespace
} // ls namespace



/*-----------------------------------------------------------------------------
 * Necessary System Header Files
-----------------------------------------------------------------------------*/
#if defined(LS_ARCH_X86)

    #if defined(LS_COMPILER_GNU)
        #include <x86intrin.h> // _rdtsc()
    #elif defined(LS_COMPILER_MSC)
        #include <intrin.h> // _rdtsc()
    #endif

    #include <immintrin.h> // _mm_pause()
#endif

#if defined(LS_ARCH_ARM)
    #include <arm_acle.h> // __yield(), __cdp()
#endif

#if defined(LS_OS_UNIX)
    #include <sys/time.h> // gettimeofday()
    #include <time.h> // clock_gettime(), clock_nanosleep(), nanosleep(), struct timespec
#endif

#include <chrono> // std::chrono
#include <thread> // std::this_thread::yield()




/*-----------------------------------------------------------------------------
 * Performance Counters
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * x86 performance counters
-------------------------------------*/
#if defined(LS_ARCH_X86)

inline LS_INLINE int64_t ls::setup::cpu_read_ticks() noexcept
{
    #if defined(LS_COMPILER_MSC)
        return (int64_t)__rdtsc();
    #else
        return _rdtsc();
    #endif
}



/*-------------------------------------
 * ARMv8 performance counters
-------------------------------------*/
#elif defined(LS_ARCH_AARCH64) && defined(LS_COMPILER_GNU)

inline LS_INLINE int64_t ls::setup::cpu_read_ticks() noexcept
{
    int64_t timer;
    __asm__ volatile("mrs %0, cntvct_el0" : "=r"(timer));
    return timer;
}



/*-------------------------------------
 * Linux performance counters
-------------------------------------*/
#elif defined(LS_OS_LINUX)

inline LS_INLINE int64_t ls::setup::cpu_read_ticks() noexcept
{
    struct timespec tv;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tv);
    return static_cast<int64_t>(tv.tv_sec) * 1000000000l + tv.tv_nsec;
}



/*-------------------------------------
 * POSIX performance counters
-------------------------------------*/
#elif defined(LS_OS_UNIX)

inline LS_INLINE int64_t ls::setup::cpu_read_ticks() noexcept
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return static_cast<int64_t>(tv.tv_sec) * 1000000l + tv.tv_usec;
}



/*-------------------------------------
 * Default performance counter using std::chrono::nanoseconds
-------------------------------------*/
#else

inline LS_INLINE int64_t ls::setup::cpu_read_ticks() noexcept
{
    const std::chrono::high_resolution_clock::duration&& d = std::chrono::high_resolution_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(d).count();
}


#endif



/*-----------------------------------------------------------------------------
 * Yielding
-----------------------------------------------------------------------------*/
#if defined(LS_ARCH_X86)

inline LS_INLINE void ls::setup::cpu_yield() noexcept
{
    _mm_pause();
}



#elif defined(LS_ARCH_AARCH64) && defined(LS_COMPILER_CLANG)

inline LS_INLINE void ls::setup::cpu_yield() noexcept
{
    __yield();
}



#elif defined(LS_ARCH_ARM) && defined(LS_COMPILER_GNU)

inline LS_INLINE void ls::setup::cpu_yield() noexcept
{
    __asm__ volatile("yield" : : : "memory");
}



#elif defined(LS_OS_UNIX)

inline LS_INLINE void ls::setup::cpu_yield() noexcept
{
    struct timespec sleepAmt;
    sleepAmt.tv_sec = 0;
    sleepAmt.tv_nsec = 1;

    #if defined(LS_OS_LINUX) || defined(LS_OS_ANDROID)
        clock_nanosleep(CLOCK_MONOTONIC_RAW, 0, &sleepAmt, nullptr);
    #else
        nanosleep(&sleepAmt, nullptr);
    #endif
}



#else

inline LS_INLINE void ls::setup::cpu_yield() noexcept
{
    std::this_thread::yield();
}


#endif



#endif /* LS_SETUP_CPU_H */
