add_library(mmdb_diskhash OBJECT
    disk_bucket.C
    bucket_array.C
    disk_hash.C
)
target_link_libraries(mmdb_diskhash PRIVATE mmdb_build_options)
set_target_properties(mmdb_diskhash PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_diskhash PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
