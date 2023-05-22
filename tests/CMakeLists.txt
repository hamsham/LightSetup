
# -------------------------------------
# Project Setup
# -------------------------------------
project(ls_setup_tests CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)



# -------------------------------------
# Include Paths
# -------------------------------------
include_directories(".")



# -------------------------------------
# Building and Linking Targets
# -------------------------------------
function(LS_SETUP_ADD_TARGET target sources)
    add_executable(${target} ${sources} ${ARGN})
    target_link_libraries(${target} LightSky::Setup)
    ls_configure_cxx_target(${target})
endfunction(LS_SETUP_ADD_TARGET)

LS_SETUP_ADD_TARGET(lssetup_cpu_timer_test lssetup_cpu_timer_test.cpp)
LS_SETUP_ADD_TARGET(lssetup_types_test     lssetup_types_test.cpp)
