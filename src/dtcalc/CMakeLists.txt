add_executable(dtcalc
    calctool.c
    ds_common.c
    ds_popup.c
    ds_widget.c
    ds_xlib.c
    functions.c
    help.c
    motif.c
    mp.c
    text.c
    text.h
    calctool.h
    ds_popup.h
    ds_xlib.h
    patchlevel.h
    ds_common.h
    ds_widget.h
    motif.h
)
target_link_libraries(dtcalc PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama m)
target_include_directories(dtcalc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/DtSvc/include)
install(TARGETS dtcalc RUNTIME DESTINATION bin)
