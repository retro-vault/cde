find_program(TIC_EXECUTABLE tic REQUIRED)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/DtTermFallBackResources.c
        ${CMAKE_CURRENT_BINARY_DIR}/dtterm.ti
    COMMAND ${CMAKE_COMMAND} -DPREPROCESSOR=$<TARGET_FILE:tradcpp>
        -DSOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} -DOUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}
        -P ${PROJECT_SOURCE_DIR}/cmake/GenerateTerminalResources.cmake
    DEPENDS tradcpp Dtterm.ad.src mkfallbk terminfoChecklist terminfoCreate
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/fallback.src VERBATIM)
add_executable(dtterm DtTermLogit.c DtTermMain.c sunDtTermServer.c DtTermSyntax.c
    ${CMAKE_CURRENT_BINARY_DIR}/DtTermFallBackResources.c)
target_include_directories(dtterm PRIVATE ${PROJECT_SOURCE_DIR}/lib/DtTerm/TermPrim
    ${PROJECT_SOURCE_DIR}/lib/DtTerm/Term ${PROJECT_SOURCE_DIR}/lib/DtTerm/TermView)
target_compile_definitions(dtterm PRIVATE SUN_TERMINAL_SERVER)
target_link_libraries(dtterm PRIVATE cde_build_options DtTerm DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/terminfo.stamp
    COMMAND ${TIC_EXECUTABLE} -o ${CMAKE_CURRENT_BINARY_DIR}/terminfo ${CMAKE_CURRENT_BINARY_DIR}/dtterm.ti
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/terminfo.stamp
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/dtterm.ti VERBATIM)
add_custom_target(dtterm_terminfo ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/terminfo.stamp)
cde_resource(Dtterm Dtterm.ad.src share/dt/app-defaults/C NO_INSTALL)
install(TARGETS dtterm RUNTIME DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/terminfo/ DESTINATION share/terminfo)
