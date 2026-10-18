add_library(mmdb_oliasdb OBJECT
    asciiIn_filters.C
    collectionIterator.C
    dlp_hd.C
    doc_hd.C
    graphic_hd.C
    locator_hd.C
    mark.C
    mark_base.C
    mmdb.C
    node_hd.C
    olias_funcs.C
    stylesheet_hd.C
    toc_hd.C
    user_base.C
)
target_link_libraries(mmdb_oliasdb PRIVATE mmdb_build_options)
set_target_properties(mmdb_oliasdb PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(mmdb_oliasdb PRIVATE NO_DB_LOCK)
target_include_directories(mmdb_oliasdb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
