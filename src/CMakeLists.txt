PROJECT(Yart CXX)
cmake_minimum_required(VERSION 2.8)

file(GLOB *.h HEADERS)

set(SOURCES
	runloop/runloop.cpp
	runloop/runloop_mgr.cpp
	)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_library(yart ${SOURCES} ${HEADERS})
