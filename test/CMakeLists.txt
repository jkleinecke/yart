

set(SOURCES
	runloop.cpp
	refcount.cpp
	pcqueue_functionality.cpp
	pcqueue_threaded.cpp
	)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../src)

add_executable(runTests ${SOURCES})
target_link_libraries(runTests yart ${CONAN_LIBS})

enable_testing()
add_test(NAME allTests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        COMMAND runTests)
