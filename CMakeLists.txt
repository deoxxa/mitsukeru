CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(mitsukeru)
CMAKE_POLICY(SET CMP0014 OLD)

#
# Project version
#
SET(${PROJECT_NAME}_MAJOR_VERSION 0)
SET(${PROJECT_NAME}_MINOR_VERSION 1)
SET(${PROJECT_NAME}_PATCH_LEVEL 0)

#
# set default build to Debug
#
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug
    CACHE STRING "Choose the type of build, options are: Debug, Profile, Release"
    FORCE
  )
ENDIF()

#
# Configure paths
#
SET(CONFIG_DIR_BIN bin/)
SET(CONFIG_DIR_ETC etc/${PROJECT_NAME}/)
SET(CONFIG_DIR_LIB lib/${PROJECT_NAME}/)

SET(EXECUTABLE_OUTPUT_PATH bin)
SET(LIBRARY_OUTPUT_PATH bin)

#
# Set compiler specific build flags
#

# g++
IF(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "-Werror -W -Wall -Wno-unused -pedantic")
  SET(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -O0 -g")
  SET(CMAKE_CXX_FLAGS_PROFILE "-DDEBUG -g -pg")
  SET(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3 -s")
ENDIF()

# msvc++
IF(MSVC_IDE)
  SET(CMAKE_CXX_FLAGS "/DWIN32 /D_CONSOLE /DZLIB_WINAPI /fp:fast /EHsc")
  SET(CMAKE_CXX_FLAGS_DEBUG "/DDEBUG /D_DEBUG /MTd /Zi")
  SET(CMAKE_CXX_FLAGS_RELEASE "/MT /D_SECURE_SCL=0")
ENDIF(MSVC_IDE)

SET(mitsukeru_source
  src/app.cpp
  src/mitsukeru/tokeniser.cpp
)
SOURCE_GROUP(${PROJECT_NAME} FILES ${mitsukeru_source})

INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(vendor)

ADD_SUBDIRECTORY(src)

SET(TARGET mitsukeru)
MESSAGE(STATUS "Target: ${TARGET}")
ADD_EXECUTABLE(${TARGET} ${${TARGET}_source})
