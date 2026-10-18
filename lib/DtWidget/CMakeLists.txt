add_library(DtWidget SHARED
    ComboBox.c
    Control.c
    DialogBox.c
    DtMsgs.c
    DtStrDefs.c
    EditAreaData.c
    EditCalls.c
    Editor.c
    Icon.c
    MenuButton.c
    NewCvt.c
    SearchCalls.c
    SearchDlg.c
    SpinBox.c
    TitleBox.c
    View.c
)
target_link_libraries(DtWidget PRIVATE cde_build_options DtSvc)
target_include_directories(DtWidget PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(DtWidget PROPERTIES VERSION 2.0.0 SOVERSION 2)
target_link_options(DtWidget PRIVATE -Wl,--no-undefined)
install(TARGETS DtWidget LIBRARY DESTINATION lib)
target_include_directories(DtWidget PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
