add_library(mmdb_hmphf OBJECT
    buckets.C
    mphf_funcs.C
    mphf_hash_table.C
    params.C
    pattern.C
    sorter.C
)
target_link_libraries(mmdb_hmphf PRIVATE mmdb_build_options)
set_target_properties(mmdb_hmphf PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_hmphf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
