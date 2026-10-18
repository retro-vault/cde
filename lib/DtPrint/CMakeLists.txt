add_library(DtPrint SHARED
    PrintMsgs.c
    PrintDlgMgr.c
    PrintOptions.c
    PrintSetupB.c
    PsubDefProc.c
    PsubUtil.c
)
target_link_libraries(DtPrint PRIVATE cde_build_options DtSvc)
target_include_directories(DtPrint PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(DtPrint PROPERTIES VERSION 2.0.0 SOVERSION 2)
target_link_options(DtPrint PRIVATE -Wl,--no-undefined)
install(TARGETS DtPrint LIBRARY DESTINATION lib)
