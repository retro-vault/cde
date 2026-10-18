add_executable(dthello
    dthello.c
)
target_link_libraries(dthello PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama m)
target_include_directories(dthello PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/DtSvc/include)
install(TARGETS dthello RUNTIME DESTINATION bin)
cde_resource(Dthello Dthello.src share/dt/app-defaults/C NO_INSTALL)
