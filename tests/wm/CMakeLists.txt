find_program(XVFB_RUN xvfb-run REQUIRED)
add_executable(test_wm_manage test_manage.c)
target_compile_definitions(test_wm_manage PRIVATE _POSIX_C_SOURCE=200809L)
target_link_libraries(test_wm_manage PRIVATE X11::X11)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/home)
add_test(NAME Dtwm.manage_window
    COMMAND ${CMAKE_COMMAND} -E env HOME=${CMAKE_CURRENT_BINARY_DIR}/home
        TTPATH=${PROJECT_BINARY_DIR}/src/desktop-data
        TTAUTHORITY=${CMAKE_CURRENT_BINARY_DIR}/home/authority
        ${XVFB_RUN} -a $<TARGET_FILE:ttsession> -c $<TARGET_FILE:test_wm_manage> $<TARGET_FILE:dtwm>)
set_tests_properties(Dtwm.manage_window PROPERTIES TIMEOUT 35
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/session-home)
add_test(NAME Dtsession.start_desktop
    COMMAND ${CMAKE_COMMAND} -E env HOME=${CMAKE_CURRENT_BINARY_DIR}/session-home
        PATH=${CMAKE_INSTALL_PREFIX}/bin:$ENV{PATH}
        XFILESEARCHPATH=${CDE_DATA_TOP}/app-defaults/%L/%N
        TTPATH=${PROJECT_BINARY_DIR}/src/desktop-data
        TTAUTHORITY=${CMAKE_CURRENT_BINARY_DIR}/session-home/authority
        ${XVFB_RUN} -a $<TARGET_FILE:ttsession> -c $<TARGET_FILE:test_wm_manage>
        ${CMAKE_INSTALL_PREFIX}/bin/dtsession session)
set_tests_properties(Dtsession.start_desktop PROPERTIES TIMEOUT 35
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/login-home)
add_test(NAME Dtsession.login_session
    COMMAND ${CMAKE_COMMAND} -E env HOME=${CMAKE_CURRENT_BINARY_DIR}/login-home
        USER=cde-test LOGNAME=cde-test SHELL=/bin/ksh LANG=C.UTF-8
        PATH=${CMAKE_INSTALL_PREFIX}/bin:$ENV{PATH}
        TTAUTHORITY=${CMAKE_CURRENT_BINARY_DIR}/login-home/authority
        ${XVFB_RUN} -a $<TARGET_FILE:test_wm_manage> ${CMAKE_INSTALL_PREFIX}/bin/Xsession xsession)
set_tests_properties(Dtsession.login_session PROPERTIES TIMEOUT 35
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_executable(test_wm_resize test_resize.c)
add_dependencies(test_wm_resize xephyr_resize test_xephyr_stale_mode)
target_compile_definitions(test_wm_resize PRIVATE XEPHYR_RESIZE_HELPER="$<TARGET_FILE:xephyr_resize>"
    XEPHYR_STALE_MODE="$<TARGET_FILE:test_xephyr_stale_mode>")
target_compile_definitions(test_wm_resize PRIVATE _POSIX_C_SOURCE=200809L)
target_compile_options(test_wm_resize PRIVATE -Wall -Wextra -Werror)
target_link_libraries(test_wm_resize PRIVATE cde_build_options DtSvc tt_build_options X11::X11 X11::Xrandr X11::Xinerama ${CMAKE_DL_LIBS})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/resize-home)
add_test(NAME Dtwm.dynamic_resolution
    COMMAND ${CMAKE_COMMAND} -E env HOME=${CMAKE_CURRENT_BINARY_DIR}/resize-home
        PATH=${CMAKE_INSTALL_PREFIX}/bin:$ENV{PATH} LANG=C
        XFILESEARCHPATH=${CDE_DATA_TOP}/app-defaults/%L/%N
        TTPATH=${PROJECT_BINARY_DIR}/src/desktop-data
        TTAUTHORITY=${CMAKE_CURRENT_BINARY_DIR}/resize-home/authority
        ${XVFB_RUN} -a -s "-screen 0 1800x1200x24"
        $<TARGET_FILE:ttsession> -c $<TARGET_FILE:test_wm_resize> $<TARGET_FILE:dtwm>)
set_tests_properties(Dtwm.dynamic_resolution PROPERTIES TIMEOUT 50
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/resize-session-home)
add_test(NAME Dtsession.dynamic_resolution
    COMMAND ${CMAKE_COMMAND} -E env HOME=${CMAKE_CURRENT_BINARY_DIR}/resize-session-home
        PATH=${CMAKE_INSTALL_PREFIX}/bin:$ENV{PATH} LANG=C.UTF-8 SHELL=/bin/ksh
        XFILESEARCHPATH=${CDE_DATA_TOP}/app-defaults/%L/%N
        TTAUTHORITY=${CMAKE_CURRENT_BINARY_DIR}/resize-session-home/authority
        ${XVFB_RUN} -a -s "-screen 0 1800x1200x24"
        $<TARGET_FILE:test_wm_resize> ${CMAKE_INSTALL_PREFIX}/bin/Xsession session)
set_tests_properties(Dtsession.dynamic_resolution PROPERTIES TIMEOUT 50
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
