
# -------------------------------------
# Project Setup
# -------------------------------------
project(LightSetup CXX)
set(OUTPUT_NAME lssetup)



# -------------------------------------
# Source Paths
# -------------------------------------
include_directories("include")

set(LS_SETUP_SOURCES
    "src/setup/setup.cpp"
)



# -------------------------------------
# Library Setup
# -------------------------------------
add_library("${OUTPUT_NAME}" STATIC "${LS_SETUP_SOURCES}"
)



# -------------------------------------
# Library Installation Setup
# -------------------------------------
install(TARGETS "${OUTPUT_NAME}" ARCHIVE DESTINATION lib)
install(DIRECTORY include/lightsky/setup DESTINATION include/lightsky)
