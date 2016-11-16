cmake_minimum_required(VERSION 3.5)
project(ditwo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(HEADER_FILES
        Src/Structures/VectorTest.h
        Src/Allocators/Allocator.h
        )
set(SOURCE_FILES
        Src/Structures/Vector.cpp
        Src/Allocators/Allocator.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")
INCLUDE(AddGTest)
if (AddGTest_FOUND)
    set(TEST_SOURCE_FILES
            Test/Main.cpp Test/Structures/VectorTest.cpp)
    add_executable(ditwoTesting ${HEADER_FILES} ${TEST_SOURCE_FILES})

    add_dependencies(ditwoTesting gtest)
    target_link_libraries(ditwoTesting
            debug ${GTEST_DEBUG_LIBRARIES}
            optimized ${GTEST_RELEASE_LIBRARIES}
            )
endif (AddGTest_FOUND)

ADD_LIBRARY(ditwo STATIC ${SOURCE_FILES} ${HEADER_FILES})