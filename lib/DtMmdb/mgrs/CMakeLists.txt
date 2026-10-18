add_library(mmdb_mgrs OBJECT
    managers.C
    misc.C
    query_mgr.C
    template_mgr.C
)
target_link_libraries(mmdb_mgrs PRIVATE mmdb_build_options)
set_target_properties(mmdb_mgrs PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(mmdb_mgrs PRIVATE COMPACTED_DISK_REP)
target_include_directories(mmdb_mgrs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
