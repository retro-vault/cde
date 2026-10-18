add_executable(dtdspmsg
    dtdspmsg.c
)
target_link_libraries(dtdspmsg PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama)
install(TARGETS dtdspmsg RUNTIME DESTINATION bin)
