add_executable(test_desktop_launch test_launch.c)
target_compile_definitions(test_desktop_launch PRIVATE _POSIX_C_SOURCE=200809L)
target_compile_options(test_desktop_launch PRIVATE -Wall -Wextra -Werror)
target_link_libraries(test_desktop_launch PRIVATE X11::X11 ${CMAKE_DL_LIBS})
find_program(XVFB_RUN xvfb-run REQUIRED)
foreach(app dtinfo dtbuilder ttsnoop dtcalc dtfile dtterm dtpad dtstyle dticon dtcreate dthelpview dtprintinfo dtmail dtcm)
    string(SUBSTRING ${app} 1 -1 class_suffix)
    set(class D${class_suffix})
    if(app STREQUAL dtbuilder)
        set(class Dtbuilder)
    elseif(app STREQUAL ttsnoop)
        set(class Ttsnoop)
    endif()
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${app}-home)
    set(wm_path "")
    if(app STREQUAL dtfile)
        set(wm_path ${CMAKE_INSTALL_PREFIX}/bin/dtwm)
    endif()
    set(arguments)
    if(app STREQUAL dtinfo)
        set(arguments -l ${CDE_DATA_TOP}/infolib/en_US.UTF-8/cde.dti)
    elseif(app STREQUAL dthelpview)
        set(arguments -helpVolume Intromgr)
    elseif(app STREQUAL dtterm)
        set(arguments -e /bin/sleep 10)
    elseif(app STREQUAL dtpad)
        set(arguments -standAlone)
    elseif(app STREQUAL dtfile)
        set(arguments -dir ${CMAKE_CURRENT_BINARY_DIR}/${app}-home)
    endif()
    if(app STREQUAL dtmail)
        file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${app}-home/Inbox
            "From test@example.invalid Sun Oct 18 12:00:00 2026\nFrom: test@example.invalid\nTo: reader@example.invalid\nSubject: CDE mailbox test\n\nMailbox reading works.\n\n")
        list(APPEND arguments -f ${CMAKE_CURRENT_BINARY_DIR}/${app}-home/Inbox)
    endif()
    add_test(NAME Desktop.${app}_window
        COMMAND ${CMAKE_COMMAND} -E env
            HOME=${CMAKE_CURRENT_BINARY_DIR}/${app}-home CDE_TEST_WM=${wm_path}
            PATH=${CMAKE_INSTALL_PREFIX}/bin:$ENV{PATH}
            XFILESEARCHPATH=${CDE_DATA_TOP}/app-defaults/%L/%N
            LANG=C TTPATH=${PROJECT_BINARY_DIR}/src/desktop-data
            TTAUTHORITY=${CMAKE_CURRENT_BINARY_DIR}/${app}-home/authority
            ${XVFB_RUN} -a $<TARGET_FILE:ttsession> -c
            $<TARGET_FILE:test_desktop_launch> ${class} ${CMAKE_INSTALL_PREFIX}/bin/${app} ${arguments})
    set_tests_properties(Desktop.${app}_window PROPERTIES TIMEOUT 20
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endforeach()
add_test(NAME Appmanager.gather_actions
    COMMAND ${CMAKE_COMMAND} -DPROGRAM=${CMAKE_INSTALL_PREFIX}/bin/dtappgather
        -DDATA_DIR=${CDE_DATA_TOP} -DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR}/gather
        -P ${CMAKE_CURRENT_SOURCE_DIR}/GatherActions.cmake)
set_tests_properties(Appmanager.gather_actions PROPERTIES TIMEOUT 10)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ims-home)
add_test(NAME InputMethod.linux_configuration
    COMMAND ${CMAKE_COMMAND} -E env HOME=${CMAKE_CURRENT_BINARY_DIR}/ims-home LANG=C.UTF-8
        ${XVFB_RUN} -a ${CMAKE_INSTALL_PREFIX}/bin/dtimsstart -list)
set_tests_properties(InputMethod.linux_configuration PROPERTIES TIMEOUT 10
    PASS_REGULAR_EXPRESSION "none")

# Exercise action lookup and ToolTalk activation, as used by the front panel.
foreach(action XclockDig Dtmail DtLoadInfoLib)
    set(class XClock)
    if(action STREQUAL Dtmail)
        set(class Dtmail)
    elseif(action STREQUAL DtLoadInfoLib)
        set(class Dtinfo)
    endif()
    set(action_home ${CMAKE_CURRENT_BINARY_DIR}/action-${action}-home)
    file(MAKE_DIRECTORY ${action_home})
    # A fresh Xephyr session starts with an empty inbox.
    file(WRITE ${action_home}/Inbox "")
    add_test(NAME Desktop.action_${action}
        COMMAND ${CMAKE_COMMAND} -E env HOME=${action_home} CDE_TEST_ACTION=1
            DTINFOLIBDEFAULT=cde DTINFOLIBSEARCHPATH=${CDE_DATA_TOP}/infolib/%L/%I.dti
            MAIL=${action_home}/Inbox LANG=C PATH=${CMAKE_INSTALL_PREFIX}/bin:$ENV{PATH}
            XFILESEARCHPATH=${CDE_DATA_TOP}/app-defaults/%L/%N
            TTPATH=${PROJECT_BINARY_DIR}/src/desktop-data TTAUTHORITY=${action_home}/authority
            ${XVFB_RUN} -a $<TARGET_FILE:ttsession> -c $<TARGET_FILE:test_desktop_launch>
            ${class} ${CMAKE_INSTALL_PREFIX}/bin/dtaction ${action})
    set_tests_properties(Desktop.action_${action} PROPERTIES TIMEOUT 20
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endforeach()
