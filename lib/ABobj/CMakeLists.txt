add_library(ABobj STATIC
    obj.c
    obj_action.c
    obj_alloc.c
    obj_fields.c
    obj_geometry.c
    obj_init.c
    obj_isa.c
    obj_names_list.c
    obj_list.c
    obj_lists.c
    obj_notify.c
    obj_release.c
    obj_scoped.c
    obj_select.c
    obj_tree.c
    obj_utils.c
    trav.c
    travP.c
    trav_public.c
    trav_safe.c
)
target_link_libraries(ABobj PUBLIC builder_build_options AButil)
target_include_directories(ABobj PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
