find_package(BISON REQUIRED)
find_library(UIL_LIBRARY Uil REQUIRED)
bison_target(builder_bil bil_parse.y ${CMAKE_CURRENT_BINARY_DIR}/bil_parse.c
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/bil_parse.h)
add_library(ABil STATIC
    abuil_load.c
    abuil_print.c
    abuil_resource_attr_map.c
    abuil_trav.c
    abuil_widget_obj_map.c
    bil.c
    bil_lexer.c
    bil_loadact.c
    bil_loadatt.c
    bil_loadfile.c
    bil_loadobj.c
    bil_store.c
    gil.c
    gil_loadact.c
    gil_loadatt.c
    gil_loadfile.c
    gil_loadobj.c
    load.c
    ${BISON_builder_bil_OUTPUTS}
)
target_link_libraries(ABil PUBLIC builder_build_options ABobjXm ${UIL_LIBRARY} ${MRM_LIBRARY})
target_include_directories(ABil PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ABil PRIVATE ${PROJECT_SOURCE_DIR}/lib/ABobj)
