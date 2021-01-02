list (APPEND tiredis_includes ${KVPROTO_INCLUDE_DIR} ${tiRedis_INCLUDE_DIR} ${fiu_include_dirs})

list(APPEND tiredis_libs
    kvproto
    ti_redis
    ${Protobuf_LIBRARY}
    Poco::Net
    Poco::JSON
    Poco::Foundation
    gtest_main
    fiu)

add_executable(tiredis_server TiRedis.cc)
target_include_directories(tiredis_server PUBLIC ${tiredis_includes})
target_link_libraries(tiredis_server ${tiredis_libs} )
