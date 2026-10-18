# The development launcher needs this only for Xephyr's stale CRTC geometry.
add_executable(xephyr_resize resize.c)
target_link_libraries(xephyr_resize PRIVATE X11::X11 X11::Xrandr)
target_compile_options(xephyr_resize PRIVATE -Wall -Wextra -Wpedantic -Werror)
set_target_properties(xephyr_resize PROPERTIES OUTPUT_NAME xephyr-resize)
install(TARGETS xephyr_resize RUNTIME DESTINATION libexec/cde)
