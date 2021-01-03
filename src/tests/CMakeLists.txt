list (APPEND test_includes ${KVPROTO_INCLUDE_DIR} ${tiRedis_INCLUDE_DIR} ${fiu_include_dirs})

list(APPEND test_libs
    kvproto
    ti_redis
    ${Protobuf_LIBRARY}
    Poco::Net
    Poco::JSON
    gtest_main
    fiu)

add_subdirectory(buffer_test)
add_subdirectory(thread_pool_test)
