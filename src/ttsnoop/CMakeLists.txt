set(snoop_dir ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${snoop_dir})
set(snoop_sources
    ${snoop_dir}/ttsnoop.C
    ${snoop_dir}/dtb_utils.c
    ${snoop_dir}/ttsnoop_ui.c
    ${snoop_dir}/ttsnoop_stubs.C
    ${snoop_dir}/apiTracer_ui.c
    ${snoop_dir}/apiTracer_stubs.C
    ${snoop_dir}/ttChooser_ui.c
    ${snoop_dir}/ttChooser_stubs.C
    ${snoop_dir}/patternProps_ui.c
    ${snoop_dir}/patternProps_stubs.C
    ${snoop_dir}/stringChooser_ui.c
    ${snoop_dir}/stringChooser_stubs.C
    ${snoop_dir}/messageProps_ui.c
    ${snoop_dir}/messageProps_stubs.C
    ${snoop_dir}/sessionChooser_ui.c
    ${snoop_dir}/sessionChooser_stubs.C
    ${snoop_dir}/fileChooser_ui.c
    ${snoop_dir}/fileChooser_stubs.C
    ${snoop_dir}/argChooser_ui.c
    ${snoop_dir}/argChooser_stubs.C
    ${snoop_dir}/callbackChooser_ui.c
    ${snoop_dir}/callbackChooser_stubs.C
)
set(snoop_headers
    ${snoop_dir}/ttsnoop.h
    ${snoop_dir}/dtb_utils.h
    ${snoop_dir}/ttsnoop_ui.h
    ${snoop_dir}/apiTracer_ui.h
    ${snoop_dir}/ttChooser_ui.h
    ${snoop_dir}/patternProps_ui.h
    ${snoop_dir}/stringChooser_ui.h
    ${snoop_dir}/messageProps_ui.h
    ${snoop_dir}/sessionChooser_ui.h
    ${snoop_dir}/fileChooser_ui.h
    ${snoop_dir}/argChooser_ui.h
    ${snoop_dir}/callbackChooser_ui.h
)
set(snoop_inputs
    argChooser.bil
    ttChooser.bil
    argChooser_stubs.C.src
    patternProps.bil
    sessionChooser.bil
    ttsnoop.C.src
    messageProps_stubs.C.src
    callbackChooser_stubs.C.src
    stringChooser_stubs.C.src
    fileChooser_stubs.C.src
    tt_c++.h
    closeBrace.h
    ttsnoop.bil
    callbackChooser.bil
    ttsnoop_stubs.C.src
    DtTt.h
    apiTracer.bil
    ttsnoop.bip
    patternProps_stubs.C.src
    Ttsnoop.src
    sessionChooser_stubs.C.src
    externC.h
    fileChooser.bil
    ttChooser_stubs.C.src
    messageProps.bil
    stringChooser.bil
    apiTracer_stubs.C.src
)
add_custom_command(OUTPUT ${snoop_dir}/generated.stamp
    BYPRODUCTS ${snoop_sources} ${snoop_headers}
    COMMAND ${CMAKE_COMMAND} -DSOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} -DOUTPUT_DIR=${snoop_dir} -DCODEGEN=$<TARGET_FILE:dtcodegen> -P ${CMAKE_CURRENT_SOURCE_DIR}/GenerateUI.cmake
    DEPENDS dtcodegen ${snoop_inputs} GenerateUI.cmake VERBATIM)
add_custom_target(ttsnoop_ui DEPENDS ${snoop_dir}/generated.stamp)
add_executable(ttsnoop ${snoop_sources} tt_c++.C DtTt.C)
add_dependencies(ttsnoop ttsnoop_ui)
target_include_directories(ttsnoop PRIVATE ${snoop_dir} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ttsnoop PRIVATE cde_build_options DtTerm DtWidget DtHelp DtSvc tt)
install(TARGETS ttsnoop RUNTIME DESTINATION bin)
cde_resource(Ttsnoop Ttsnoop.src share/dt/app-defaults/C)
