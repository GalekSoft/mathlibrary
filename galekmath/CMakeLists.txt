cmake_minimum_required(VERSION 2.8.4)
project(GalekMath)
set(LIBRARIES_FROM_REFERENCES "")


file(GLOB SOURCE
    "*.h"
    "*.cpp"
)

add_library(Platform ${SOURCE})
#target_link_libraries(Platform "${LIBRARIES_FROM_REFERENCES}")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")