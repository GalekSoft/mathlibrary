cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -fexceptions -w -fpermissive")
set(LIBRARIES_FROM_REFERENCES "")

project(GalekMath)


set(LIBRARIES_FROM_REFERENCES "")
file(GLOB SOURCE
    "galekmath/*.h"
    "galekmath/*.cpp"
)

add_library(GalekMath ${SOURCE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

IF(WIN32) # Check if we are on Windows
 
 if(MSVC) # Check if we are using the Visual Studio compiler
    SET(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} /SUBSYSTEM:WINDOWS") # Tell the project how to behave in this environment
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Tell the project how to behave in this environment
  else()
    message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
  endif()

elseif(UNIX)


if(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -fexceptions -w -fpermissive")
add_definitions(-D__LINUX__)

else()
  message(SEND_ERROR "You are on an unsupported platform! (Not Win32 or Unix)")
ENDIF()

ENDIF()


option(USE_DOUBLE_PRECISION_ENABLE "USE_DOUBLE_PRECISION" OFF)
if(USE_DOUBLE_PRECISION_ENABLE)
  set(USE_DOUBLE_PRECISION ON)
endif()

CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/galekmath/galekmath_config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/galekmath_config.h")
	

set(SOURCE_FILES ${SOURCE})