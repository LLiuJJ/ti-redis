add_executable(buffer_test BufferTests.cc)
target_include_directories(buffer_test PUBLIC ${test_includes})
target_link_libraries(buffer_test ${test_libs})
