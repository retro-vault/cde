add_library(ABobjXm STATIC
    objxm_args.c
    objxm_config.c
    objxm_conn.c
    objxm_inst.c
    objxm_objects.c
    objxm_strs.c
    objxm_util.c
)
target_link_libraries(ABobjXm PUBLIC builder_build_options ABobj DtWidget DtTerm DtHelp)
target_include_directories(ABobjXm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
