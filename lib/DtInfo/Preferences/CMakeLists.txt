add_library(info_Preferences OBJECT
    UserPreference.C
    IntegerPref.C
    BooleanPref.C
    StringPref.C
    WindowGeometryPref.C
)
target_link_libraries(info_Preferences PRIVATE info_build_options)
target_include_directories(info_Preferences PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
