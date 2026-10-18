add_library(info_Graphics OBJECT
    PixmapGraphic.C
)
target_link_libraries(info_Graphics PRIVATE info_build_options)
target_include_directories(info_Graphics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
