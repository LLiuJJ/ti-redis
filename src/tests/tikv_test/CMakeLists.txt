add_executable(tikv_cli_test TikvCliTests.cc)
target_include_directories(tikv_cli_test PUBLIC ${test_includes})
target_link_libraries(tikv_cli_test ${test_libs})
