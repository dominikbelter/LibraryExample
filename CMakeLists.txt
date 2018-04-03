# cmake requirements
cmake_minimum_required(VERSION 2.8)

# Build options have to be before PROJECT(...)
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE PATH "Configuration types")
SET(CMAKE_BUILD_TYPE "Release" CACHE PATH "Current build configuration")

# Example Project configuration
PROJECT(TUTORIAL_LIBRARY)
SET(CMAKE_CXX_FLAGS "-std=c++14 -pthread")

# Folders
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Settings
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")

# core libraries
option(BUILD_LIB_ROBOT "Build Lib Robot" ON)
mark_as_advanced(BUILD_LIB_ROBOT)

# demos
option(BUILD_LIB_ROBOT_DEMO "Build LIB Robot Demo" ON)
mark_as_advanced(BUILD_LIB_ROBOT_DEMO)

# Executable output directory
SET(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin${OUTPUT_DIRECTORY_POSTFIX} CACHE PATH "Executable output directory")
mark_as_advanced(RUNTIME_OUTPUT_DIRECTORY)

# Dynamic library output directory
SET(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin${OUTPUT_DIRECTORY_POSTFIX} CACHE PATH "Dynamic library output directory")
mark_as_advanced(LIBRARY_OUTPUT_DIRECTORY)

# Static library output directory
SET(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib${OUTPUT_DIRECTORY_POSTFIX} CACHE PATH "Static library output directory")
mark_as_advanced(ARCHIVE_OUTPUT_DIRECTORY)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ARCHIVE_OUTPUT_DIRECTORY})
foreach(CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
	string(TOUPPER ${CONFIGURATION_TYPE} CONFIGURATION_TYPE)
	SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${RUNTIME_OUTPUT_DIRECTORY})
	SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${LIBRARY_OUTPUT_DIRECTORY})
	SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${ARCHIVE_OUTPUT_DIRECTORY})
endforeach(CONFIGURATION_TYPE CMAKE_CONFIGURATION_TYPES)

if (MSVC)
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif()

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR CMake)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# Create the RobotConfig.cmake
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
file(RELATIVE_PATH REL_LIB_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_LIB_DIR}")

set(CONF_INCLUDE_DIRS "${RELATIVE_PATH}" "${CMAKE_SOURCE_DIR}")

set(CONF_LIB_DIRS "${RELATIVE_PATH}" "/build/lib")

configure_file(RobotConfig.cmake.in
  "${CMAKE_SOURCE_DIR}/RobotConfig.cmake" @ONLY)

# ... for the install tree
set(CONF_INCLUDE_DIRS "${CONF_INCLUDE_DIRS}/include")
set(CONF_LIB_DIRS "${CMAKE_SOURCE_DIR}/build/lib")

configure_file(RobotConfig.cmake.in
  "${CMAKE_SOURCE_DIR}/RobotConfig.cmake" @ONLY)

# Install the RobotConfig.cmake
install(FILES
  "${CMAKE_SOURCE_DIR}/RobotConfig.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)


###############################################################################
#
# Robot library
#
###############################################################################

if(BUILD_LIB_ROBOT)
        file(GLOB ROBOT_SOURCES
            "${CMAKE_SOURCE_DIR}/src/Robot/*.cpp"
        )
        file(GLOB ROBOT_HEADERS
            "${CMAKE_SOURCE_DIR}/include/Robot/*.h"
        )

        ADD_LIBRARY(Robot STATIC ${ROBOT_SOURCES} ${ROBOT_HEADERS})
#        TARGET_LINK_LIBRARIES(Robot Utilities)
        INSTALL(TARGETS Robot RUNTIME DESTINATION bin LIBRARY DESTINATION bin ARCHIVE DESTINATION lib)
        INSTALL(FILES ${ROBOT_HEADERS} DESTINATION include/Robot/)
endif(BUILD_LIB_ROBOT)

###############################################################################
#
# Robot DEMO executables
#
###############################################################################

if(BUILD_LIB_ROBOT_DEMO)
        SET(DEMO_SOURCES ./main.cpp)
        ADD_EXECUTABLE(robotTest ${DEMO_SOURCES})
        TARGET_LINK_LIBRARIES(robotTest Robot)
        INSTALL(TARGETS robotTest RUNTIME DESTINATION bin)
endif(BUILD_LIB_ROBOT_DEMO)
