find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(TIRPC REQUIRED IMPORTED_TARGET GLOBAL libtirpc)
add_library(tt_build_options INTERFACE)
target_include_directories(tt_build_options INTERFACE
    ${PROJECT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/mini_isam ${PROJECT_BINARY_DIR}/include)
target_compile_definitions(tt_build_options INTERFACE
    _DEFAULT_SOURCE _POSIX_C_SOURCE=200809L HAVE_CONFIG_H OPT_TIRPC
    CPP_PROGRAM="/usr/bin/cpp" TT_VERSION_STRING="CDE Version ${PROJECT_VERSION}"
    CDE_LIBEXEC_DIR="${CDE_LIBEXEC_DIR}"
    CDE_INSTALLATION_TOP="${CDE_INSTALLATION_TOP}" CDE_DATA_TOP="${CDE_DATA_TOP}"
    CDE_CONFIGURATION_TOP="${CDE_CONFIGURATION_TOP}" CDE_LOGFILES_TOP="${CDE_LOGFILES_TOP}")
target_link_libraries(tt_build_options INTERFACE PkgConfig::TIRPC Threads::Threads X11::Xt X11::X11 ${CMAKE_DL_LIBS})
target_compile_options(tt_build_options INTERFACE
    -Wall -Wextra
    $<$<COMPILE_LANGUAGE:C>:-Werror=implicit-function-declaration;-Werror=int-to-pointer-cast;-Werror=pointer-to-int-cast>)
add_subdirectory(mini_isam)
add_subdirectory(lib/api/c)
add_subdirectory(lib/api/dnd)
add_subdirectory(lib/db)
add_subdirectory(lib/mp)
add_subdirectory(lib/util)
add_subdirectory(lib/tttk)
add_subdirectory(slib)
add_library(tt SHARED
    $<TARGET_OBJECTS:tt_api> $<TARGET_OBJECTS:tt_dnd>
    $<TARGET_OBJECTS:tt_db> $<TARGET_OBJECTS:tt_mp>
    $<TARGET_OBJECTS:tt_util> $<TARGET_OBJECTS:tt_tttk>)
target_link_libraries(tt PRIVATE tt_build_options PUBLIC PkgConfig::TIRPC)
target_include_directories(tt PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
set_target_properties(tt PROPERTIES VERSION 2.0.0 SOVERSION 2 LINKER_LANGUAGE CXX)
target_link_options(tt PRIVATE -Wl,--no-undefined)
install(TARGETS tt LIBRARY DESTINATION lib)
install(FILES ${PROJECT_SOURCE_DIR}/include/Tt/tt_c.h
    ${PROJECT_SOURCE_DIR}/include/Tt/tttk.h DESTINATION include/Tt)
