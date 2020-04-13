
# -------------------------------------
# Project Setup
# -------------------------------------
project(LightSetup CXX)
set(OUTPUT_NAME lssetup)



# -------------------------------------
# Source Paths
# -------------------------------------
include_directories(include)

set(LS_SETUP_SOURCES
    src/Setup.cpp
)

set(LS_SETUP_HEADERS
    include/lightsky/setup/Api.h
    include/lightsky/setup/Arch.h
    include/lightsky/setup/Compiler.h
    include/lightsky/setup/Macros.h
    include/lightsky/setup/OS.h
    include/lightsky/setup/Setup.h
    include/lightsky/setup/Types.h
)



# -------------------------------------
# Library Setup
# -------------------------------------
option(BUILD_SHARED_LIBS "Build Shared Libraries" OFF)

if (BUILD_SHARED_LIBS)
    target_compile_options(${OUTPUT_NAME} INTERFACE -DLS_BUILD_SHARED -DLS_SHARED)
    set(LS_LIB_TYPE SHARED)
else()
    set(LS_LIB_TYPE STATIC)
endif()

add_library(${OUTPUT_NAME} ${LS_LIB_TYPE} ${LS_SETUP_SOURCES} ${LS_SETUP_HEADERS})



# -------------------------------------
# Build Options
# -------------------------------------
if (CMAKE_BUILD_TYPE)
    string(TOLOWER ${CMAKE_BUILD_TYPE} _CURRENT_BUILD_TYPE)
    if(${_CURRENT_BUILD_TYPE} STREQUAL debug OR ${_CURRENT_BUILD_TYPE} STREQUAL relwithdebinfo)
        message("-- Debug mode enabled.")
        target_compile_definitions(${OUTPUT_NAME} INTERFACE -DLS_DEBUG)
    else()
        message("-- Release mode enabled.")
    endif()
endif()



include(CheckIncludeFile)
include(CheckCXXCompilerFlag)
include(CheckCXXSymbolExists)

check_include_file(immintrin.h HAVE_X86_SIMD)
check_include_file(arm_neon.h HAVE_ARM_SIMD)

check_cxx_compiler_flag(-march=arm-v7a HAVE_ARM_V7A)
check_cxx_compiler_flag(-march=armv8-a HAVE_ARM_V8A)

if (HAVE_X86_SIMD)
    option(ENABLE_X86_OPTIMIZATIONS "Enable x86-specific compiler optimization flags." ON)
endif()

if (HAVE_ARM_V7A OR HAVE_ARM_V8A)
    if (HAVE_ARM_SIMD)
        option(ENABLE_ARM_OPTIMIZATIONS "Enable arm-specific compiler optimization flags." ON)
    endif()
endif()

option(ENABLE_PROFILING "Enable profiling (recommended for release builds with debug information)." OFF)



# -------------------------------------
# Compiler Options
# -------------------------------------

# Fix broken search paths on OS X
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories(SYSTEM /usr/local/include)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${OUTPUT_NAME}
        INTERFACE
            -Wall
            -Werror
            -Wextra
            -pedantic
            -pedantic-errors
            -Wno-implicit-fallthrough
            -Wno-pessimizing-move
            -ftree-vectorize
            -ffast-math
            -funsafe-math-optimizations
            -fno-stack-protector)

    if (ENABLE_PROFILING)
        message("-- Profiling enabled")
        target_compile_options(${OUTPUT_NAME} INTERFACE -pg)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg -Og") # failsafe
    else()
        target_compile_options(${OUTPUT_NAME} INTERFACE -fomit-frame-pointer)
    endif()

    if (ENABLE_ARM_OPTIMIZATIONS)
        message("-- ARM compiler optimizations enabled.")

        if (HAVE_ARM_V7A)
            target_compile_options(${OUTPUT_NAME}
                INTERFACE
                    -mhard-float
                    -mfloat-abi=hard
                    -mfpu=neon-vfpv4+fp16
                    -mno-unaligned-access)
        elseif(HAVE_ARM_V8A)
            target_compile_options(${OUTPUT_NAME}
                INTERFACE
                    -march=armv8-a+fp16+simd
                    #-march=armv8-a
                    #-mfpu=neon-fp16
                    #-mfp16-format=ieee
                    -faligned-new)
        endif()
    endif()

    if (ENABLE_X86_OPTIMIZATIONS)
        message("-- x86 compiler optimizations enabled.")
        target_compile_options(${OUTPUT_NAME}
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
                -mbmi)  # TZCNT

        if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            target_compile_options(${OUTPUT_NAME}
                INTERFACE
                    -mno-avx256-split-unaligned-load
                    -mno-avx256-split-unaligned-store
                    -mfpmath=both)
        endif()
    endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    if (ENABLE_X86_OPTIMIZATIONS)
        target_compile_options(${OUTPUT_NAME} INTERFACE /arch:AVX2) # enable AVX2
    endif()

    target_compile_options(${OUTPUT_NAME}
        INTERFACE
            /GL # global program optimization
            /Gw # Whole-program optimization
            /GA # Windows program optimizations
            /MT # Enable multi-threaded application linking
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
            /fp:fast)
    #target_compile_options(${OUTPUT_NAME} INTERFACE /Gv) # Enable __vectorcall conventions
    #target_compile_options(${OUTPUT_NAME} INTERFACE /Ox) # Optimize, optimize, optimize

    # Prevent libraries from being rebuilt
    set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    /LTCG:INCREMENTAL")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /LTCG:INCREMENTAL")
    set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} /LTCG:INCREMENTAL")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /LTCG:INCREMENTAL")

    # Extra enabled warnings
    target_compile_options(${OUTPUT_NAME}
        INTERFACE
            /we4700 # Enable check for use of uninitialized variables
            /we4533) # Code initializing a variable will not be executed

    # Disabled warnings
    target_compile_options(${OUTPUT_NAME}
        INTERFACE
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
            /wd4244) # possible loss of data when converting between time_t and unsigned int
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options(${OUTPUT_NAME}
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
            -mtune=core2
            -march=core2
            -ip
            -vecabi=gcc
            -fp-model fast=2
            -finline
            -gcc)
else()
    message(FATAL_ERROR "Your compiler is currently unsupported: ${CMAKE_CXX_COMPILER_ID}")
endif()



# -------------------------------------
# Library Installation Setup
# -------------------------------------
install(TARGETS ${OUTPUT_NAME}
    EXPORT LightSetup
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(DIRECTORY include/lightsky/setup DESTINATION include/lightsky)

install(EXPORT LightSetup
    FILE LightSetup.cmake
    NAMESPACE LightSky::
    DESTINATION lib/cmake/LightSky
)

export(EXPORT LightSetup NAMESPACE LightSky::)
add_library(LightSky::Setup ALIAS lssetup)
