cmake_minimum_required (VERSION 2.8)
project (nokkhum-processor)

# The version number.
set (nokkhum-processor_VERSION_MAJOR 0)
set (nokkhum-processor_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/nokkhum_processor_config.h.in"
  "${PROJECT_BINARY_DIR}/nokkhum_processor_config.h"
  )
  

# define library usage
find_package(PkgConfig)
pkg_check_modules(OPENCV REQUIRED "opencv >= 2.3")
pkg_check_modules(LIBGLOG REQUIRED "libglog >= 0.3")

set (BOOST_LIBRARIES "-lboost_thread -lboost_filesystem -lboost_system -lboost_date_time")
set (OPENCV_LIBRARIES "-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect -lopencv_video -lopencv_features2d")
set (JSON_SPIRIT_LIBRARIES "-ljson_spirit")
set (CPPUNIT_LIBRARIES "-lcppunit")


link_libraries(
	${OPENCV_LIBRARIES}
	${BOOST_LIBRARIES}
	${LIBGLOG_LIBRARIES}
	${JSON_SPIRIT_LIBRARIES}
    ${CPPUNIT_LIBRARIES}
)
 
file(GLOB_RECURSE nokkhum_processor_CXX_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "../../src/config/*.cpp")
 
# complier
set (CMAKE_CXX_COMPILER g++)
add_definitions(-std=c++11)
set (CMAKE_VERBOSE_MAKEFILE TRUE)

set (CMAKE_CXX_FLAGS_DEBUG, "-g -Wall")
set (CMAKE_CXX_FLAGS "-Wall")

# add the binary tree to the search path for include files
# so that we will find nokkhum_processor_config.h
include_directories ("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}" "../../src")


# add the executable
add_executable (nokkhum-processor ${nokkhum_processor_CXX_SOURCES})
# target_link_libraries (nokkhum-processor  ${EXTRA_LIBS})

# add the install targets
install (TARGETS nokkhum-processor DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/nokkhum_processor_config.h" 
  DESTINATION include)
