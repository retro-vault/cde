add_library(mmdb_index OBJECT
    btree_index.C
    dyn_disk_index.C
    dyn_index.C
    dyn_memory_index.C
    fast_mphf.C
    hash.C
    index.C
    inv_lists.C
    mphf_index.C
)
target_link_libraries(mmdb_index PRIVATE mmdb_build_options)
set_target_properties(mmdb_index PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_index PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
