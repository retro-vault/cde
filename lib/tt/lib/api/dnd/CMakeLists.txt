add_library(tt_dnd OBJECT
    ttdnd.c
)
target_link_libraries(tt_dnd PRIVATE tt_build_options)
set_target_properties(tt_dnd PROPERTIES POSITION_INDEPENDENT_CODE ON)
