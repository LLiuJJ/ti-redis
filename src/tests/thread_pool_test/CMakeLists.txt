add_executable(thread_pool_test ThreadPoolTests.cc)
target_include_directories(thread_pool_test PUBLIC ${test_includes})
target_link_libraries(thread_pool_test ${test_libs})
