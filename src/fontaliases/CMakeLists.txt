find_program(BDFTOPCF_EXECUTABLE bdftopcf REQUIRED)
find_program(MKFONTDIR_EXECUTABLE mkfontdir REQUIRED)
find_program(GZIP_EXECUTABLE gzip REQUIRED)
add_executable(mk_fonts_alias mk_fonts_alias.c)
target_link_libraries(mk_fonts_alias PRIVATE cde_build_options)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/dtinfo.pcf.gz ${CMAKE_CURRENT_BINARY_DIR}/fonts.dir ${CMAKE_CURRENT_BINARY_DIR}/fixed.alias ${CMAKE_CURRENT_BINARY_DIR}/mixed.alias
    COMMAND ${CMAKE_COMMAND} -DBDFTOPCF=${BDFTOPCF_EXECUTABLE} -DMKFONTDIR=${MKFONTDIR_EXECUTABLE} -DGZIP=${GZIP_EXECUTABLE} -DALIASES=$<TARGET_FILE:mk_fonts_alias> -DSOURCE=${CMAKE_CURRENT_SOURCE_DIR}/dtinfo.bdf -DOUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR} -P ${CMAKE_CURRENT_SOURCE_DIR}/GenerateFonts.cmake
    DEPENDS mk_fonts_alias dtinfo.bdf GenerateFonts.cmake VERBATIM)
add_custom_target(desktop_fontaliases ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/dtinfo.pcf.gz ${CMAKE_CURRENT_BINARY_DIR}/fonts.dir ${CMAKE_CURRENT_BINARY_DIR}/fixed.alias ${CMAKE_CURRENT_BINARY_DIR}/mixed.alias)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/dtinfo.pcf.gz ${CMAKE_CURRENT_BINARY_DIR}/fonts.dir ${CMAKE_CURRENT_BINARY_DIR}/fixed.alias ${CMAKE_CURRENT_BINARY_DIR}/mixed.alias DESTINATION share/dt/fontaliases)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/mixed.alias DESTINATION etc/dt/fontaliases RENAME fonts.alias)
