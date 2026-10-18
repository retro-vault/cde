add_executable(dtaction
    Main.c
)
target_link_libraries(dtaction PRIVATE cde_build_options DtPrint DtHelp DtWidget DtSvc tt DtXinerama m)
target_include_directories(dtaction PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib/DtSvc/include)
install(TARGETS dtaction RUNTIME DESTINATION bin)
find_library(CRYPT_LIBRARY crypt REQUIRED)
target_link_libraries(dtaction PRIVATE ${CRYPT_LIBRARY})
