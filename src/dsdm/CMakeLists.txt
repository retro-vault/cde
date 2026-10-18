add_executable(dsdm
    dsdm.c
    proxy.c
)
target_link_libraries(dsdm PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama m)
target_include_directories(dsdm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/DtSvc/include)
install(TARGETS dsdm RUNTIME DESTINATION bin)
