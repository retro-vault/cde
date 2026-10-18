# Interactive lifecycle test helper; not a CTest case because it closes a window
# on the developer's parent display. Invoke only against the test's Xephyr ID.
add_executable(test_xephyr_close_window close_window.c)
target_compile_options(test_xephyr_close_window PRIVATE -Wall -Wextra -Werror)
target_link_libraries(test_xephyr_close_window PRIVATE X11::X11)

add_library(test_xephyr_stale_mode SHARED stale_mode.c)
target_compile_definitions(test_xephyr_stale_mode PRIVATE _GNU_SOURCE)
target_compile_options(test_xephyr_stale_mode PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(test_xephyr_stale_mode PRIVATE X11::Xrandr ${CMAKE_DL_LIBS})
