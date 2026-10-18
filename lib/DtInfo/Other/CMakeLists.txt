add_library(info_Other OBJECT
    AppPrintData.C
    WindowSystemMotif.C
)
target_link_libraries(info_Other PRIVATE info_build_options)
target_include_directories(info_Other PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
