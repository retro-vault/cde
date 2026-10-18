add_library(info_cgm OBJECT
    cgmcmds.c
    cgmcommon.c
    cgmio.c
    cgmtext.c
    getcgm.c
)
target_link_libraries(info_cgm PRIVATE info_build_options)
target_include_directories(info_cgm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
