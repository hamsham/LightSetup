/*
 * File:   setup/macros.h
 * Author: Miles Lacey
 *
 * This file contains macros and definitions used throughout LightSky
 */

#ifndef LS_SETUP_MACROS_H
#define LS_SETUP_MACROS_H

#include <type_traits>

#include "lightsky/setup/Arch.h"
#include "lightsky/setup/Compiler.h"

/*
 * Preprocessor Stringify
 */
#ifndef LS_STRINGIFY
    #define LS_STRINGIFY(x) #x
#endif /* LS_STRINGIFY */

/*
 * Maximum value
 */
#ifndef LS_MAX
    #define LS_MAX(x, y) ((x > y) ? x : y)
#endif

/*
 * Minimum Value
 */
#ifndef LS_MIN
    #define LS_MIN(x, y) ((x < y) ? x : y)
#endif

/*
 * Get the number of elements contained in a stack-allocated array.
 */
#ifndef LS_ARRAY_SIZE
    #define LS_ARRAY_SIZE( a ) ( sizeof( a ) / sizeof( a[0] ) )
#endif

/*
 * Class Template Declaration
 *
 * This macro declares a template class as "extern," providing the ability to
 * use non-instantiated templated classes. It also provides a typedef in order
 * to give each template type an alias.
 */
#ifndef LS_DECLARE_CLASS_TYPE
    #define LS_DECLARE_CLASS_TYPE(nickName, name, ...)\
            typedef name<__VA_ARGS__> nickName; \
            extern template class name<__VA_ARGS__>
#endif

/*
 * Class Template Definitions
 *
 * This macro is used to explicitly instantiate templated classes.
 */
#ifndef LS_DEFINE_CLASS_TYPE
    #define LS_DEFINE_CLASS_TYPE(name, ...) template class name<__VA_ARGS__>
#endif

/*
 * Struct Template Declaration
 *
 * This macro declares a template class as "extern," providing the ability to
 * use non-instantiated templated classes. It also provides a typedef in order
 * to give each template type an alias.
 */
#ifndef LS_DECLARE_STRUCT_TYPE
    #define LS_DECLARE_STRUCT_TYPE(nickName, name, ...)\
            typedef name<__VA_ARGS__> nickName; \
            extern template struct name<__VA_ARGS__>
#endif

/*
 * Struct Template Definitions
 *
 * This macro is used to explicitly instantiate templated classes.
 */
#ifndef LS_DEFINE_STRUCT_TYPE
    #define LS_DEFINE_STRUCT_TYPE(name, ...) template struct name<__VA_ARGS__>
#endif

/*
 * Union Template Declaration
 *
 * This macro declares a template class as "extern," providing the ability to
 * use non-instantiated templated classes. It also provides a typedef in order
 * to give each template type an alias.
 */
#ifndef LS_DECLARE_UNION_TYPE
    #define LS_DECLARE_UNION_TYPE(nickName, name, ...)\
            typedef name<__VA_ARGS__> nickName; \
            extern template union name<__VA_ARGS__>
#endif

/*
 * Union Template Definitions
 *
 * This macro is used to explicitly instantiate templated classes.
 */
#ifndef LS_DEFINE_UNION_TYPE
    #define LS_DEFINE_UNION_TYPE(name, ...) template union name<__VA_ARGS__>
#endif

/*
 * The LS_ENUM_VAL macro will extract the numerical value of any type declared
 * using "enum class." A compiler error will be thrown if the input argument is
 * not an enumeration.
 */
#ifndef LS_ENUM_VAL
    #define LS_ENUM_VAL( x ) static_cast<std::underlying_type<decltype(x)>::type>(x)
#endif

/*
 * LS_UNREACHABLE() uses internal compiler intrinsics (not hardware
 * intrinsics) to provide the compiler with a hint that no code at the place
 * of the macro can be executed. This allows for optimizers to elide some code
 * and reduce the number of instructions emitted.
 */
#if defined(LS_COMPILER_GNU) || defined(LS_COMPILER_CLANG)
    #define LS_UNREACHABLE() __builtin_unreachable()
#elif defined(LS_COMPILER_MSC)
    #define LS_UNREACHABLE() __assume(0)
#else
    #define LS_UNREACHABLE() do {} while(0)
#endif

/*
 * LS_PREFETCH Permits data in memory to be prefetched and loaded into cache
 * for execution. Using the cache-level and read/write hints can permit the
 * compiler to determine which cache-level should be used to store the
 * prefetched data.
 */
#ifndef LS_ARCH_X86
    #ifndef LS_PREFETCH_LEVEL_NONTEMPORAL
        #define LS_PREFETCH_LEVEL_NONTEMPORAL 0
    #endif

    #ifndef LS_PREFETCH_LEVEL_L1
        #define LS_PREFETCH_LEVEL_L1 1
    #endif

    #ifndef LS_PREFETCH_LEVEL_L2
        #define LS_PREFETCH_LEVEL_L2 2
    #endif

    #ifndef LS_PREFETCH_LEVEL_L3
        #define LS_PREFETCH_LEVEL_L3 3
    #endif

#else
    #include <immintrin.h>

    #ifndef LS_PREFETCH_LEVEL_NONTEMPORAL
        #define LS_PREFETCH_LEVEL_NONTEMPORAL _MM_HINT_NTA
    #endif

    #ifndef LS_PREFETCH_LEVEL_L1
        #define LS_PREFETCH_LEVEL_L1 _MM_HINT_T0
    #endif

    #ifndef LS_PREFETCH_LEVEL_L2
        #define LS_PREFETCH_LEVEL_L2 _MM_HINT_T1
    #endif

    #ifndef LS_PREFETCH_LEVEL_L3
        #define LS_PREFETCH_LEVEL_L3 _MM_HINT_T2
    #endif

#endif



#ifndef LS_PREFETCH_ACCESS_R
    #define LS_PREFETCH_ACCESS_R 0
#endif

#ifndef LS_PREFETCH_ACCESS_RW
    #define LS_PREFETCH_ACCESS_RW 1
#endif



#if defined(LS_ARCH_X86)
    #define LS_PREFETCH(p, rw, level) _mm_prefetch((const char*)(p), level)

#elif defined(LS_ARCH_AARCH64) && defined(LS_COMPILER_CLANG)
    #include <arm_acle.h>
    #define LS_PREFETCH(p, rw, level) __pldx(rw, level > 2 ? 2 : level, level != 0, p)

#elif defined(LS_COMPILER_GNU) || defined(LS_COMPILER_CLANG)
    #define LS_PREFETCH(p, rw, level) __builtin_prefetch((const void*)(p), rw, level)

#else
    #define LS_PREFETCH(p, rw, level)
#endif

#if defined(LS_COMPILER_GNU) || defined(LS_COMPILER_CLANG)
    #ifndef LS_LIKELY
        #define LS_LIKELY(x) __builtin_expect((x), 1)
    #endif

    #ifndef LS_UNLIKELY
        #define LS_UNLIKELY(x) __builtin_expect((x), 0)
    #endif
#else
    #ifndef LS_LIKELY
        #define LS_LIKELY(x) (x)
    #endif

    #ifndef LS_UNLIKELY
        #define LS_UNLIKELY(x) (x)
    #endif
#endif



namespace ls
{
namespace setup
{

template <unsigned bytesToPrefetch, unsigned rw, unsigned level>
inline void sized_prefetch(const void* pData) noexcept
{
    constexpr unsigned fetchCount = ((bytesToPrefetch > 512 ? 512 : bytesToPrefetch) + 63) / 64;
    const char* p = reinterpret_cast<const char*>(pData);

    switch (fetchCount/64)
    {
        case 8:  LS_PREFETCH(p+448, rw, level);
        case 7:  LS_PREFETCH(p+384, rw, level);
        case 6:  LS_PREFETCH(p+320, rw, level);
        case 5:  LS_PREFETCH(p+256, rw, level);
        case 4:  LS_PREFETCH(p+192, rw, level);
        case 3:  LS_PREFETCH(p+128, rw, level);
        case 2:  LS_PREFETCH(p+64,  rw, level);
        default: LS_PREFETCH(p+0,   rw, level);
    }
}

} // end setup namespace
} // end ls namespace



#endif /* LS_SETUP_MACROS_H */
