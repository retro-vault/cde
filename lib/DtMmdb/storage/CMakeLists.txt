add_library(mmdb_storage OBJECT
    abs_storage.C
    chunks_index.C
    heap_comp_funcs.C
    lru.C
    page.C
    page_cache.C
    page_rep.C
    page_storage.C
    rep_cell.C
    rep_policy.C
    unixf_storage.C
    version.C
    vm_storage.C
)
target_link_libraries(mmdb_storage PRIVATE mmdb_build_options)
set_target_properties(mmdb_storage PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_storage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
