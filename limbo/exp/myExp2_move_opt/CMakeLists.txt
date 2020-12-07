cmake_minimum_required (VERSION 3.0)

PROJECT(Bayes_Optim)

set (CMAKE_CXX_STANDARD 14)

include_directories("/usr/include/eigen3")
include_directories("/usr/local/include")
include_directories("/usr/include/boost")
include_directories("/usr/include/tbb")
include_directories("../../src")

# Add nlopt
find_package(NLopt REQUIRED)
link_directories("/usr/local/lib")
MESSAGE("NLopt version : ${NLopt_VERSION}")
MESSAGE("NLopt INCLUDE_DIRS : ${NLopt_INCLUDE_DIRS}")
MESSAGE("NLopt LIB_DIR : ${NLopt_LIB_DIR}")

# Add Move Monitor
add_library(MoveCounter SHARED MoveCounter.cpp)

# Add boost
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS filesystem system) 

# Link to all necessary libraries
ADD_EXECUTABLE(main  main.cpp )
target_link_libraries( main Boost::filesystem Boost::system)
target_link_libraries(main MoveCounter)

target_link_libraries(main "nlopt")
target_link_libraries(main m)
