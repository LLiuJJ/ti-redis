cmake_minimum_required(VERSION 2.8)
project(tiRedis)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-narrowing")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET(CMAKE_CXX_FLAGS_DEBUG  "-g -Wall -std=c++0x")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -g -Wall -std=c++0x")
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(CMAKE_CXX_FLAGS_DEBUG  "-g -Wall -std=c++1y -stdlib=libc++ -Wc++11-extensions")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -g -Wall -std=c++1y -stdlib=libc++ -Wc++11-extensions")
ELSE()
    message(FATAL_ERROR "Only support linux or OS X, support for windows is in plan")
ENDIF()

enable_testing()

if (NOT gRPC_FOUND)
    include (cmake/find_grpc.cmake)
endif ()

if (NOT Poco_Foundation_LIBRARY)
    include (cmake/find_poco.cmake)
endif()

if (NOT KVPROTO_FOUND)
    include (cmake/find_kvproto.cmake)
endif ()

if (NOT GTEST_FOUND AND ENABLE_TESTS)
    include (cmake/find_gtest.cmake)
endif()

add_subdirectory (third_party)
add_subdirectory (src)
