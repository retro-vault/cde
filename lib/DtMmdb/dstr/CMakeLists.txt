add_library(mmdb_dstr OBJECT
    set.C
    bset.C
    slist.C
    dlist_cell.C
    dlist.C
    heap.C
    void_ptr_array.C
    void_ptr_stack.C
    memory_pool.C
    index_agent.C
    token_stack.C
    slist_char_ptr_cell.C
)
target_link_libraries(mmdb_dstr PRIVATE mmdb_build_options)
set_target_properties(mmdb_dstr PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_dstr PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
