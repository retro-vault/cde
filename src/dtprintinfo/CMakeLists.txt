find_program(KSH_EXECUTABLE ksh REQUIRED)
find_program(AWK_EXECUTABLE awk REQUIRED)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/dtprintinfo_msg.h ${CMAKE_CURRENT_BINARY_DIR}/dtprintinfo.msg ${CMAKE_CURRENT_BINARY_DIR}/dtprintinfo_cat.h
    COMMAND ${CMAKE_COMMAND} -DPROGRAM=${KSH_EXECUTABLE} -DCPP=$<TARGET_FILE:tradcpp> -DSOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} -DOUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR} -DAWK=${AWK_EXECUTABLE} -P ${CMAKE_CURRENT_SOURCE_DIR}/GenerateMessages.cmake
    DEPENDS tradcpp sym2num msg.awk dtprintinfo.msg.src VERBATIM)
add_executable(dtprintinfo
    util/Invoke.C
    util/Process.C
    libUI/BaseUI.C
    libUI/MotifUI/Application.C
    libUI/MotifUI/LabelObj.C
    libUI/MotifUI/Button.C
    libUI/MotifUI/MainWindow.C
    libUI/MotifUI/ComboBoxObj.C
    libUI/MotifUI/MenuBar.C
    libUI/MotifUI/Container.C
    libUI/MotifUI/Menu.C
    libUI/MotifUI/Dialog.C
    libUI/MotifUI/MotifThread.C
    libUI/MotifUI/DtDND.C
    libUI/MotifUI/MotifUI.C
    libUI/MotifUI/Group.C
    libUI/MotifUI/Prompt.C
    libUI/MotifUI/HelpSystem.C
    libUI/MotifUI/ScaleObj.C
    libUI/MotifUI/Sep.C
    libUI/MotifUI/IconObj.C
    libUI/MotifUI/Debug.c
    libUI/MotifUI/Icon.c
    libUI/MotifUI/WorkArea.c
    objects/BaseObj.C
    objects/PrintObj/ParseJobs.C
    objects/PrintObj/PrintSubSys.C
    objects/PrintObj/PrintJob.C
    objects/PrintObj/Queue.C
    UI/DtActions.C
    UI/DtProps.C
    UI/DtFindSet.C
    UI/DtSetPref.C
    UI/DtApp.C
    UI/DtPrtJobIcon.C
    UI/DtMainW.C
    UI/DtWorkArea.C
    UI/DtDetailsLabel.C
    UI/DtPrtProps.C
    UI/DtPrinterIcon.C
    UI/DtFindD.C
    UI/DtSetModList.C
    DtPrintinfo.C ${CMAKE_CURRENT_BINARY_DIR}/dtprintinfo_msg.h)
target_include_directories(dtprintinfo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} UI libUI util libUI/MotifUI objects objects/PrintObj)
target_compile_definitions(dtprintinfo PRIVATE KORNSHELL="${KSH_EXECUTABLE}")
target_link_libraries(dtprintinfo PRIVATE cde_build_options DtSvc tt)
install(TARGETS dtprintinfo RUNTIME DESTINATION bin)
cde_message_catalog(dtprintinfo ${CMAKE_CURRENT_BINARY_DIR}/dtprintinfo.msg)
add_dependencies(catalog_dtprintinfo dtprintinfo)
