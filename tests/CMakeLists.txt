
# -------------------------------------
# Project Setup
# -------------------------------------
project(ls_setup_tests CXX)



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
endfunction(LS_SETUP_ADD_TARGET)

LS_SETUP_ADD_TARGET(lssetup_cpu_timer_test lssetup_cpu_timer_test.cpp)

