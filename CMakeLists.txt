
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
)



# -------------------------------------
# Library Setup
# -------------------------------------
option(BUILD_SHARED_LIBS "Build Shared Libraries" OFF)

if (BUILD_SHARED_LIBS)
    add_definitions(-DLS_BUILD_SHARED -DLS_SHARED)
    set(LS_LIB_TYPE SHARED)
else()
    set(LS_LIB_TYPE STATIC)
endif()

add_library(${OUTPUT_NAME} ${LS_LIB_TYPE} ${LS_SETUP_SOURCES} ${LS_SETUP_HEADERS})



# -------------------------------------
# Library Installation Setup
# -------------------------------------
install(TARGETS ${OUTPUT_NAME}
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(DIRECTORY include/lightsky/setup DESTINATION include/lightsky)
