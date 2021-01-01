# Currently kvproto should always use bundled library.

if (NOT EXISTS "${tiRedis_SOURCE_DIR}/third_party/kvproto/cpp/kvproto/errorpb.pb.h")
   message (FATAL_ERROR "kvproto submodule in third_party/kvproto is missing.")
endif ()

message(STATUS "Using kvproto: ${tiRedis_SOURCE_DIR}/third_party/kvproto/cpp")
