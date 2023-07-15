
option(ENABLE_PROFILING "Enable profiling (recommended for release builds with debug information)." OFF)



# -------------------------------------
# Optimization Options
# -------------------------------------
include(CheckIncludeFile)
include(CheckCXXCompilerFlag)
include(CheckCXXSymbolExists)

check_include_file(immintrin.h HAVE_X86_SIMD)
check_include_file(arm_neon.h HAVE_ARM_SIMD)
check_include_file(arm_neon.h HAVE_ARM_SIMD_ALT -march=armv7-a+neon-vfpv4 -mfloat-abi=hard -mhard-float -mfpu=neon-vfpv4)

check_cxx_compiler_flag(-march=armv7-a+neon-vfpv4 HAVE_ARM_V7A)
check_cxx_compiler_flag(-march=armv8-a+fp16+simd  HAVE_ARM_V8A)

if (HAVE_X86_SIMD)
    option(ENABLE_X86_OPTIMIZATIONS "Enable x86-specific compiler optimization flags." ON)
endif()

if (HAVE_ARM_V7A OR HAVE_ARM_V8A)
    if (HAVE_ARM_SIMD OR HAVE_ARM_SIMD_ALT)
        option(ENABLE_ARM_OPTIMIZATIONS "Enable arm-specific compiler optimization flags." ON)
    endif()
endif()


if (ENABLE_PROFILING)
    message("-- Profiling enabled")
endif()

if (ENABLE_ARM_OPTIMIZATIONS)
    if(HAVE_ARM_V8A)
        message("-- ARM-v8a compiler optimizations enabled.")

    elseif (HAVE_ARM_V7A)
        message("-- ARM-v7a compiler optimizations enabled.")
    endif()
endif()

if (ENABLE_X86_OPTIMIZATIONS)
    message("-- x86 compiler optimizations enabled.")
endif()



# -------------------------------------
# GCC & Clang Options
# -------------------------------------
function(_ls_configure_gnu_target target language)
    target_compile_options(${target}
        PRIVATE
            -Wall
            -Werror
            -Wextra
            -pedantic
            -pedantic-errors
            -Wno-implicit-fallthrough
            -ftree-vectorize
            -ffast-math
            -funsafe-math-optimizations
            -fno-stack-protector
    )

    string(TOUPPER ${language} targetLang)
    if (${targetLang} STREQUAL CXX)
        target_compile_options(${target} PRIVATE -Wno-pessimizing-move)
    endif()

    if (ENABLE_PROFILING)
        target_compile_options(${target} PRIVATE -pg)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg -Og") # failsafe
    else()
        target_compile_options(${target} PRIVATE -fomit-frame-pointer)
    endif()

    if (ENABLE_ARM_OPTIMIZATIONS)
        if(HAVE_ARM_V8A)
            target_compile_options(${target}
                INTERFACE
                    -march=armv8-a+fp16+simd
                    -faligned-new
            )

        elseif (HAVE_ARM_V7A)
            target_compile_options(${target}
                INTERFACE
                    -march=armv7-a+neon-vfpv4
                    -mhard-float
                    -mfloat-abi=hard
                    -mfpu=neon-vfpv4
                    -mfp16-format=ieee
                    -mno-unaligned-access
            )
        endif()
    endif()

    if (ENABLE_X86_OPTIMIZATIONS)
        target_compile_options(${target}
            INTERFACE
                -mmmx
                -msse
                -msse2
                -msse3
                -mssse3
                -msse4
                -msse4.1
                -msse4.2
                -mfma
                -mavx
                -mavx2
                -mf16c
                -mlzcnt
                -mbmi  # TZCNT
                -mbmi2
            )

        if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            target_compile_options(${target}
                INTERFACE
                    -mno-avx256-split-unaligned-load
                    -mno-avx256-split-unaligned-store
                    -mfpmath=both
            )
        endif()
    endif()
endfunction()



# -------------------------------------
# MSVC Options
# -------------------------------------
function(_ls_configure_msvc_target target language)
    if (ENABLE_X86_OPTIMIZATIONS)
        target_compile_options(${target} INTERFACE /arch:AVX2) # enable AVX2
    endif()

    target_compile_options(${target}
        PRIVATE
            /GL # global program optimization
            /Gw # Whole-program optimization
            /GA # Windows program optimizations
            /Oi # enable instrinsic functions
            /Ot # favor fast code
            /Oy # Omit frame pointers
            /permissive- # enable conformance mode
            /Wall # enable all warnings
            /GS- # Disable global security cookies
            /sdl- # Disable Security Development Lifecycle checks
            /W3 # production-quality warnings
            /WX # warnings are errors
            /Zc:rvalueCast /Zc:strictStrings /Zc:inline
            /fp:fast
    )
    #target_compile_options(${target} INTERFACE /Gv) # Enable __vectorcall conventions
    #target_compile_options(${target} INTERFACE /Ox) # Optimize, optimize, optimize

    # Prevent libraries from being rebuilt
    set_target_properties(${target} PROPERTIES LINK_FLAGS "/LTCG /IGNORE:4075")

    # Extra enabled warnings
    target_compile_options(${target}
        PRIVATE
            /we4700 # Enable check for use of uninitialized variables
            /we4533) # Code initializing a variable will not be executed

    # Disabled warnings
    target_compile_options(${target}
        PRIVATE
            /wd4146 # unsigned negation using the '-' operator
            /wd4996 # insecure use of wcstombs
            /wd4365 # Implicit conversion from signed to unsigned (built into the standard library :/ )
            /wd4820 # Padding being added to structures using "alignas"... also built into the standard libary
            /wd4571 # Catch semantics changed
            /wd4625 # Implicly deleted copy constructor
            /wd4626 # Implicly deleted copy operator
            /wd5026 # Implicly deleted move constructor
            /wd5027 # Implicly deleted move operator
            /wd4774 # Format string is not a string literal in sprintf_s
            /wd4868 # compiler may not enforce left-to-right evaluation order in braced initializer list
            /wd5039 # An 'extern "C"' function contains something which might throw an exception
            /wd4244 # possible loss of data when converting between time_t and unsigned int
            /wd4710 # Error if a function was not inlined
            /wd5045 # Insertion of spectre mitigations
            /wd4702 # Unreachable code
    )
endfunction()



# -------------------------------------
# Intel ICC Options
# -------------------------------------
function(_ls_configure_icc_target target language)
    target_compile_options(${target}
        INTERFACE
            -xAVX2
            -mmmx
            -msse
            -msse2
            -msse3
            -mssse3
            -msse4
            -msse4.1
            -msse4.2
            -mfma
            -mavx
            -mavx2
            -mf16c
            -mlzcnt
            -mbmi
            -mbmi2
            -mtune=core2
            -march=core2
            -ip
            -vecabi=gcc
            -fp-model fast=2
            -finline
            -gcc
    )
endfunction()



# -------------------------------------
# Target Setup
# -------------------------------------
# Debug Symbols
if (CMAKE_BUILD_TYPE)
    string(TOLOWER ${CMAKE_BUILD_TYPE} _CURRENT_BUILD_TYPE)
    if(${_CURRENT_BUILD_TYPE} STREQUAL debug OR ${_CURRENT_BUILD_TYPE} STREQUAL relwithdebinfo)
        set(LS_ENABLE_DEBUG_BUILD_FLAGS TRUE)
        message("-- Debug mode enabled.")
    else()
        message("-- Release mode enabled.")
    endif()
endif()

function(ls_configure_target target language)
    # Debug Symbols
    if (LS_ENABLE_DEBUG_BUILD_FLAGS)
        target_compile_definitions(${target} INTERFACE -DLS_DEBUG)
    endif()

    # Fix broken search paths on OS X
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        target_include_directories(${target} SYSTEM PRIVATE /usr/local/include)
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        _ls_configure_gnu_target(${target} ${language})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        _ls_configure_msvc_target(${target} ${language})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
        _ls_configure_icc_target(${target} ${language})
    endif()

    # MinGW doesn't always play nice with the Windows SDK
    if (MINGW)
        set(CMAKE_SYSTEM_NAME Windows)

        # These defines were made in Windows 10
        target_compile_definitions(${target} INTERFACE -DWINVER=0x0A00)
        target_compile_definitions(${target} INTERFACE -D_WIN32_WINNT=0x0A00)
    endif()

endfunction()



function(ls_configure_c_target target)
    ls_configure_target(${target} C)
endfunction()

function(ls_configure_cxx_target target)
    ls_configure_target(${target} CXX)
endfunction()
