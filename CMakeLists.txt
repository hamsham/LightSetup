
# -------------------------------------
# Project Setup
# -------------------------------------
project(LightSetup CXX)
set(OUTPUT_NAME lssetup)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

include(ls_setup.cmake)



# -------------------------------------
# Source Paths
# -------------------------------------
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
add_library(${OUTPUT_NAME} ${LS_LIB_TYPE} ${LS_SETUP_SOURCES} ${LS_SETUP_HEADERS})
target_include_directories(${OUTPUT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
ls_configure_cxx_target(${OUTPUT_NAME})



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



# -------------------------------------
# Precompiled Headers
# -------------------------------------
if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.16.0")
    option(LIGHTSKY_ENABLE_PCH "Enable the use of precompiled headers in LightSky" OFF)
endif()



# -------------------------------------
# Library Tests
# -------------------------------------
option(LS_SETUP_BUILD_TESTS "Build tests for the LightSetup library." ON)

if(LS_SETUP_BUILD_TESTS)
    add_subdirectory(tests)
endif()
