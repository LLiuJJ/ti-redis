set(TiRedis_sources)

list(APPEND TiRedis_sources kv/2pc.cc)
list(APPEND TiRedis_sources kv/Backoff.cc)
list(APPEND TiRedis_sources kv/Cluster.cc)
list(APPEND TiRedis_sources kv/LockResolver.cc)
list(APPEND TiRedis_sources kv/RegionCache.cc)
list(APPEND TiRedis_sources kv/RegionClient.cc)
list(APPEND TiRedis_sources kv/Rpc.cc)
list(APPEND TiRedis_sources kv/Snapshot.cc)
list(APPEND TiRedis_sources kv/Scanner.cc)
list(APPEND TiRedis_sources pd/Client.cc)
list(APPEND TiRedis_sources coprocessor/Client.cc)
list(APPEND TiRedis_sources RedactHelpers.cc)
list(APPEND TiRedis_sources tiredis/TiRedis.cc)

set(tiRedis_INCLUDE_DIR ${tiRedis_SOURCE_DIR}/include)

add_executable(ti_redis_server ${TiRedis_sources})

add_library(ti_redis ${TiRedis_sources})
target_include_directories(ti_redis PUBLIC ${KVPROTO_INCLUDE_DIR} ${tiRedis_INCLUDE_DIR} ${fiu_include_dirs})
target_link_libraries(ti_redis kvproto ${Poco_Foundation_LIBRARY} fiu gRPC::grpc++)
