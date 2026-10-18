add_library(DtXinerama SHARED DtXinerama.c)
target_include_directories(DtXinerama PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_link_libraries(DtXinerama PUBLIC X11::Xinerama X11::X11)
target_compile_options(DtXinerama PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wstrict-prototypes -Werror)
set_target_properties(DtXinerama PROPERTIES VERSION 2.0.0 SOVERSION 2)
install(TARGETS DtXinerama LIBRARY DESTINATION lib)
install(FILES ${PROJECT_SOURCE_DIR}/include/Dt/DtXinerama.h DESTINATION include/Dt)
