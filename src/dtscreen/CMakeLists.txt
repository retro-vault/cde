add_executable(dtscreen
    blank.c
    dtscreen.c
    flame.c
    hopalong.c
    hsbramp.c
    image.c
    life.c
    pyro.c
    qix.c
    resource.c
    rotor.c
    swarm.c
    usleep.c
    worm.c
    dtscreen.h
)
target_link_libraries(dtscreen PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama m)
target_include_directories(dtscreen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/DtSvc/include)
install(TARGETS dtscreen RUNTIME DESTINATION bin)
cde_resource(Dtscreen Dtscreen.src share/dt/app-defaults/C NO_INSTALL)
