add_library(mmdb_utility OBJECT
    funcs.C
    pm_random.C
    atoi_pearson.C
    xtime.C
    buffer.C
    atoi_larson.C
    atomic_lock.C
    rw_lock.C
    atoi_fast.C
    filter.C
    mmdb_exception.C
    randomize.C
)
target_link_libraries(mmdb_utility PRIVATE mmdb_build_options)
set_target_properties(mmdb_utility PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_utility PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
