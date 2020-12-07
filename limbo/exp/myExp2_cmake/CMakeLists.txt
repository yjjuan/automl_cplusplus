cmake_minimum_required (VERSION 3.0)

PROJECT(Chapter9)

set (CMAKE_CXX_STANDARD 14)

# Requires OpenCV
FIND_PACKAGE( OpenCV 4.0.0 REQUIRED )
MESSAGE("OpenCV version : ${OpenCV_VERSION}")
MESSAGE("OpenCV libs : ${OpenCV_LIBS}")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

# 添加Eigen头文件
include_directories("/usr/include/eigen3")
include_directories("/usr/local/include")
include_directories("/usr/include/boost")
include_directories("/usr/include/tbb")
include_directories("../../src")

# Add nlopt
find_package(NLopt REQUIRED)
#pkg_check_modules(NLOPT REQUIRED IMPORTED_TARGET nlopt)
#include_directories(${NLopt_INCLUDE_DIRS})
#link_directories(${NLopt_LIB_DIR})
link_directories("/usr/local/lib")
MESSAGE("NLopt version : ${NLopt_VERSION}")
MESSAGE("NLopt INCLUDE_DIRS : ${NLopt_INCLUDE_DIRS}")
MESSAGE("NLopt LIB_DIR : ${NLopt_LIB_DIR}")

# Add boost
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS filesystem system) 

# Link to all necessary libraries
ADD_EXECUTABLE(main  main.cpp )
TARGET_LINK_LIBRARIES( main ${OpenCV_LIBS} )
target_link_libraries( main Boost::filesystem Boost::system)

#target_link_libraries(main ${NLopt_LIBS})
target_link_libraries(main "nlopt")
target_link_libraries(main m)
