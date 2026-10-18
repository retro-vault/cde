add_executable(tradcpp array.c directive.c files.c utils.c main.c place.c
    eval.c macro.c output.c)
target_compile_definitions(tradcpp PRIVATE _DEFAULT_SOURCE)
