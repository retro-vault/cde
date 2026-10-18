add_executable(dtcm
    MonthPanel.c
    RFCMIME.c
    about.c
    alarm.c
    blist.c
    browser.c
    calendarA.c
    cm_i18n.c
    cmtt.c
    datefield.c
    dayglance.c
    deskset.c
    dnd.c
    dssw.c
    editor.c
    find.c
    fns.c
    font.c
    format.c
    goto.c
    graphics.c
    group_editor.c
    help.c
    i18nxlate.c
    icon.c
    md5.c
    misc.c
    monthglance.c
    namesvc.c
    print.c
    props.c
    props_pu.c
    reminders.c
    rfp.c
    select.c
    session.c
    submit.c
    tempbr.c
    timezone.c
    todo.c
    weekglance.c
    x_graphics.c
    yearglance.c
)
target_include_directories(dtcm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(dtcm PRIVATE DtCmP calendar_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
install(TARGETS dtcm RUNTIME DESTINATION bin)
add_executable(dtcm_delete
    cm_delete.c
)
target_include_directories(dtcm_delete PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(dtcm_delete PRIVATE DtCmP calendar_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
install(TARGETS dtcm_delete RUNTIME DESTINATION bin)
add_executable(dtcm_insert
    cm_insert.c
)
target_include_directories(dtcm_insert PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(dtcm_insert PRIVATE DtCmP calendar_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
install(TARGETS dtcm_insert RUNTIME DESTINATION bin)
add_executable(dtcm_lookup
    cm_lookup.c
)
target_include_directories(dtcm_lookup PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(dtcm_lookup PRIVATE DtCmP calendar_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
install(TARGETS dtcm_lookup RUNTIME DESTINATION bin)
add_executable(dtcm_editor
    datefield.c
    deskset.c
    dssw.c
    dtcm_editor.c
    help.c
    misc.c
    reminders.c
    rfp.c
)
target_include_directories(dtcm_editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(dtcm_editor PRIVATE DtCmP calendar_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
install(TARGETS dtcm_editor RUNTIME DESTINATION bin)
