find_library(UIL_LIBRARY Uil REQUIRED)
set(builder_generated_dir ${CMAKE_CURRENT_BINARY_DIR}/generated)
set(builder_generated_sources
    ${builder_generated_dir}/dtb_utils.c
    ${builder_generated_dir}/appfw_ui.c
    ${builder_generated_dir}/about_box_ui.c
    ${builder_generated_dir}/brws_ui.c
    ${builder_generated_dir}/color_chooser_ui.c
    ${builder_generated_dir}/conn_ui.c
    ${builder_generated_dir}/dnd_ed_ui.c
    ${builder_generated_dir}/help_ed_ui.c
    ${builder_generated_dir}/attch_ed_ui.c
    ${builder_generated_dir}/proj_ui.c
    ${builder_generated_dir}/revolv_ui.c
    ${builder_generated_dir}/button_ui.c
    ${builder_generated_dir}/choice_ui.c
    ${builder_generated_dir}/combobox_ui.c
    ${builder_generated_dir}/cpanel_ui.c
    ${builder_generated_dir}/custdlg_ui.c
    ${builder_generated_dir}/drawp_ui.c
    ${builder_generated_dir}/group_ui.c
    ${builder_generated_dir}/label_ui.c
    ${builder_generated_dir}/list_ui.c
    ${builder_generated_dir}/mainwin_ui.c
    ${builder_generated_dir}/menu_ui.c
    ${builder_generated_dir}/menubar_ui.c
    ${builder_generated_dir}/scale_ui.c
    ${builder_generated_dir}/sep_ui.c
    ${builder_generated_dir}/spinbox_ui.c
    ${builder_generated_dir}/termp_ui.c
    ${builder_generated_dir}/textf_ui.c
    ${builder_generated_dir}/textp_ui.c
    ${builder_generated_dir}/cgen_win_ui.c
    ${builder_generated_dir}/cgen_props_ui.c
    ${builder_generated_dir}/cgen_env_ui.c
    ${builder_generated_dir}/fchooser_ui.c
    ${builder_generated_dir}/message_ed_ui.c
    ${builder_generated_dir}/panedwin_ed_ui.c
    ${builder_generated_dir}/palette_ui.c
    ${builder_generated_dir}/appfw_stubs.c
    ${builder_generated_dir}/brws_stubs.c
    ${builder_generated_dir}/color_chooser_stubs.c
    ${builder_generated_dir}/conn_stubs.c
    ${builder_generated_dir}/dnd_ed_stubs.c
    ${builder_generated_dir}/help_ed_stubs.c
    ${builder_generated_dir}/attch_ed_stubs.c
    ${builder_generated_dir}/proj_stubs.c
    ${builder_generated_dir}/revolv_stubs.c
    ${builder_generated_dir}/button_stubs.c
    ${builder_generated_dir}/choice_stubs.c
    ${builder_generated_dir}/combobox_stubs.c
    ${builder_generated_dir}/cpanel_stubs.c
    ${builder_generated_dir}/custdlg_stubs.c
    ${builder_generated_dir}/drawp_stubs.c
    ${builder_generated_dir}/group_stubs.c
    ${builder_generated_dir}/label_stubs.c
    ${builder_generated_dir}/list_stubs.c
    ${builder_generated_dir}/mainwin_stubs.c
    ${builder_generated_dir}/menu_stubs.c
    ${builder_generated_dir}/menubar_stubs.c
    ${builder_generated_dir}/scale_stubs.c
    ${builder_generated_dir}/sep_stubs.c
    ${builder_generated_dir}/spinbox_stubs.c
    ${builder_generated_dir}/termp_stubs.c
    ${builder_generated_dir}/textf_stubs.c
    ${builder_generated_dir}/textp_stubs.c
    ${builder_generated_dir}/cgen_win_stubs.c
    ${builder_generated_dir}/cgen_props_stubs.c
    ${builder_generated_dir}/cgen_env_stubs.c
    ${builder_generated_dir}/fchooser_stubs.c
    ${builder_generated_dir}/message_ed_stubs.c
    ${builder_generated_dir}/palette_stubs.c
    ${builder_generated_dir}/about_box_stubs.c
    ${builder_generated_dir}/dtbuilder.c
)
set(builder_modules palette about_box brws proj conn appfw color_chooser dnd_ed help_ed attch_ed revolv button choice combobox cpanel custdlg drawp group label list mainwin menu menubar scale sep spinbox termp textf textp cgen_win cgen_props cgen_env fchooser message_ed panedwin_ed)
set(builder_module_files)
foreach(module IN LISTS builder_modules)
    list(APPEND builder_module_files ${module}.bil)
endforeach()
set(builder_generated_headers ${builder_generated_dir}/dtbuilder.h ${builder_generated_dir}/dtb_utils.h)
foreach(module IN LISTS builder_modules)
    list(APPEND builder_generated_headers ${builder_generated_dir}/${module}_ui.h)
endforeach()
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ui.stamp
    COMMAND ${CMAKE_COMMAND} -E make_directory ${builder_generated_dir}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${builder_generated_dir}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dtbuilder.c.src ${builder_generated_dir}/dtbuilder.c
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dtbuilder.msg.src ${builder_generated_dir}/dtbuilder.msg
    COMMAND ${CMAKE_COMMAND} -E env NLSPATH=${PROJECT_BINARY_DIR}/src/dtcodegen/dtcodegen.cat
        $<TARGET_FILE:dtcodegen> -merge -p dtbuilder.bip -main
    COMMAND ${CMAKE_COMMAND} -E env NLSPATH=${PROJECT_BINARY_DIR}/src/dtcodegen/dtcodegen.cat
        $<TARGET_FILE:dtcodegen> -merge -p dtbuilder.bip ${builder_module_files}
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/ui.stamp
    WORKING_DIRECTORY ${builder_generated_dir}
    DEPENDS dtcodegen ${PROJECT_BINARY_DIR}/src/dtcodegen/dtcodegen.cat dtbuilder.bip dtbuilder.c.src dtbuilder.msg.src dtbuilder.h
        palette.bil
        about_box.bil
        brws.bil
        proj.bil
        conn.bil
        appfw.bil
        color_chooser.bil
        dnd_ed.bil
        help_ed.bil
        attch_ed.bil
        revolv.bil
        button.bil
        choice.bil
        combobox.bil
        cpanel.bil
        custdlg.bil
        drawp.bil
        group.bil
        label.bil
        list.bil
        mainwin.bil
        menu.bil
        menubar.bil
        scale.bil
        sep.bil
        spinbox.bil
        termp.bil
        textf.bil
        textp.bil
        cgen_win.bil
        cgen_props.bil
        cgen_env.bil
        fchooser.bil
        message_ed.bil
        panedwin_ed.bil

    BYPRODUCTS ${builder_generated_sources} ${builder_generated_headers} ${builder_generated_dir}/dtbuilder.msg
    VERBATIM)
file(MAKE_DIRECTORY ${builder_generated_dir})
add_custom_target(dtbuilder_ui DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/ui.stamp)
add_dependencies(dtbuilder_ui builder_catalog)
add_executable(dtbuilder ${builder_generated_sources}
    ab_utils.c
    ab_bil.c
    ab_dnd.c
    ab_globals.c
    abobj_align.c
    abobj_edit.c
    abobj_list.c
    abobj_events.c
    abobj_layers.c
    abobj_layout.c
    abobj_menu.c
    abobj_move.c
    abobj_resize.c
    abobj_select.c
    abobj_set.c
    abobj_util.c
    brws.c
    brws_find.c
    brws_mthds.c
    brws_utils.c
    cgen_utils.c
    conn_drag.c
    conn_interpret.c
    conn_obj.c
    pal.c
    pal_create.c
    pal_button.c
    pal_choice.c
    pal_combobox.c
    pal_cpanel.c
    pal_custdlg.c
    pal_drawp.c
    pal_fchooser.c
    pal_group.c
    pal_label.c
    pal_list.c
    pal_mainwin.c
    pal_menu.c
    pal_menubar.c
    pal_panedwin.c
    pal_scale.c
    pal_sep.c
    pal_spinbox.c
    pal_termp.c
    pal_textf.c
    pal_textp.c
    proj.c
    proj_utils.c
    projP_utils.c
    prop.c
    prop_items.c
    tmode.c
    tmodeP.c
    ui_msg.c
    ui_list.c
    ui_util.c
    vwr.c
    x_util.c
)
add_dependencies(dtbuilder dtbuilder_ui)
target_include_directories(dtbuilder PRIVATE ${builder_generated_dir} ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(dtbuilder PRIVATE PIXMAP_WORKAROUND)
target_link_libraries(dtbuilder PRIVATE ABil ABobjXm ABobj AButil cde_build_options
    DtTerm DtHelp DtWidget DtSvc tt DtXinerama m ${UIL_LIBRARY} ${MRM_LIBRARY})
install(TARGETS dtbuilder RUNTIME DESTINATION bin)
cde_resource(Dtbuilder.raw Dtbuilder.src share/dt/app-defaults/C NO_INSTALL)
cde_localized_resource(Dtbuilder ${CMAKE_CURRENT_BINARY_DIR}/Dtbuilder.raw
    ${PROJECT_SOURCE_DIR}/src/desktop-data/messages/Dtbuilder.tmsg share/dt/app-defaults/C)
target_include_directories(dtbuilder PRIVATE ${PROJECT_SOURCE_DIR}/lib/ABobj ${PROJECT_SOURCE_DIR}/lib/AButil ${PROJECT_SOURCE_DIR}/lib/ABobjXm)

cde_message_catalog(dtbuilder ${builder_generated_dir}/dtbuilder.msg
    ${PROJECT_SOURCE_DIR}/lib/AButil/libAButil.msg
    ${PROJECT_SOURCE_DIR}/lib/ABobjXm/libABobjXm.msg
    ${PROJECT_SOURCE_DIR}/lib/ABil/libABil.msg)
add_dependencies(catalog_dtbuilder dtbuilder)
