add_executable(dtinfo main.C ${PROJECT_SOURCE_DIR}/lib/DtInfo/Support/InputNotifier.C)
target_link_libraries(dtinfo PRIVATE dtinfo_impl)
install(TARGETS dtinfo RUNTIME DESTINATION bin)

find_program(PERL_EXECUTABLE perl REQUIRED)
file(GLOB_RECURSE info_resource_sources CONFIGURE_DEPENDS resources/*.res)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Dtinfo
    COMMAND ${CMAKE_COMMAND} -DCPP=$<TARGET_FILE:tradcpp> -DPERL=${PERL_EXECUTABLE} -DSOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} -DOUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR} -P ${CMAKE_CURRENT_SOURCE_DIR}/GenerateResources.cmake
    DEPENDS tradcpp ${info_resource_sources} treeres.pl GenerateResources.cmake VERBATIM)
add_custom_target(dtinfo_resources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Dtinfo)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Dtinfo DESTINATION share/dt/app-defaults/C)

install(FILES data/mmdb.mark.spec DESTINATION share/dt/infolib/etc)
