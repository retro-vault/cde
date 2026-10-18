add_library(info_Widgets OBJECT
    Pixmap.c
    Tree.c
    Panner.c
    Simple.c
    Porthole.c
    XawInitFake.c
    TabButton.c
    Restraint.c
    WXmOpButton.C
)
target_link_libraries(info_Widgets PRIVATE info_build_options)
target_include_directories(info_Widgets PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
