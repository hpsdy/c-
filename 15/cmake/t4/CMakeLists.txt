cmake_minimum_required(VERSION 2.8)
INCLUDE(./src/cm/CmakeLists.txt)
FIND_PATH(header hello.h)
if (header)
    MESSAGE(STATUS "FIND HEADER:" ${header})
    INCLUDE_DIRECTORIES(${header})
else ()
    MESSAGE(FATAL_ERROR "NOT FIND HEADER")
endif (header)
FIND_LIBRARY(libhello libhello.so)
if (libhello)
    MESSAGE(STATUS "FIND LIB:" ${libhello})
    LINK_LIBRARIES(${libhello})
    #LINK_DIRECTORIES(${libhello})
else ()
    MESSAGE(FATAL_ERROR "NOT FIND LIB")
endif (libhello)
ADD_SUBDIRECTORY(src)
ADD_EXECUTABLE(tmain tmain.cpp)
