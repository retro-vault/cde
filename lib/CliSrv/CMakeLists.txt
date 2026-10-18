add_library(CliSrv STATIC DirIterator.C Environ.C TTFile.C UnixEnv.C cstring.C)
target_include_directories(CliSrv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CliSrv PUBLIC cde_build_options DtSvc tt)
