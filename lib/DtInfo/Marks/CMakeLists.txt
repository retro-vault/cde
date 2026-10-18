add_library(info_Marks OBJECT
    Mark.C
    Anchor.C
    Mark_mmdb.C
    MarkBase.C
    MarkBase_mmdb.C
    MarkInfo.C
)
target_link_libraries(info_Marks PRIVATE info_build_options)
target_include_directories(info_Marks PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
