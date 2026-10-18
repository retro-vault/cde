add_library(info_build_options INTERFACE)
target_include_directories(info_build_options INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/UAS/Base
    ${CMAKE_CURRENT_SOURCE_DIR}/UAS ${CMAKE_CURRENT_SOURCE_DIR}/UAS/DtSR/Util_Classes
    ${CMAKE_CURRENT_SOURCE_DIR}/wwl/include ${PROJECT_SOURCE_DIR}/lib/DtMmdb)
target_compile_definitions(info_build_options INTERFACE DtinfoClient UseWideChars
    Internationalize UseMotifXpm UseTooltalk UseSessionMgmt DTSEARCH CDE_NEXT
    EXPAND_TEMPLATES NATIVE_EXCEPTIONS)
target_link_libraries(info_build_options INTERFACE cde_build_options DtMmdb DtSearch
    DtPrint DtHelp DtWidget DtSvc tt DtXinerama m)
configure_file(Prelude.h.in Prelude.h COPYONLY)
configure_file(Support/Support.d.in Support/Support.d COPYONLY)
configure_file(Support/Support.h.in Support/Support.h COPYONLY)
add_subdirectory(Support)
configure_file(UAS/UAS.d.in UAS/UAS.d COPYONLY)
configure_file(UAS/UAS.h.in UAS/UAS.h COPYONLY)
configure_file(Basic/Basic.d.in Basic/Basic.d COPYONLY)
configure_file(Basic/Basic.h.in Basic/Basic.h COPYONLY)
add_subdirectory(Basic)
configure_file(OliasSearch/OliasSearch.d.in OliasSearch/OliasSearch.d COPYONLY)
configure_file(OliasSearch/OliasSearch.h.in OliasSearch/OliasSearch.h COPYONLY)
add_subdirectory(OliasSearch)
configure_file(Marks/Marks.d.in Marks/Marks.d COPYONLY)
configure_file(Marks/Marks.h.in Marks/Marks.h COPYONLY)
add_subdirectory(Marks)
configure_file(Graphics/Graphics.d.in Graphics/Graphics.d COPYONLY)
configure_file(Graphics/Graphics.h.in Graphics/Graphics.h COPYONLY)
add_subdirectory(Graphics)
configure_file(Preferences/Preferences.d.in Preferences/Preferences.d COPYONLY)
configure_file(Preferences/Preferences.h.in Preferences/Preferences.h COPYONLY)
add_subdirectory(Preferences)
configure_file(Managers/Managers.d.in Managers/Managers.d COPYONLY)
configure_file(Managers/Managers.h.in Managers/Managers.h COPYONLY)
add_subdirectory(Managers)
configure_file(Other/Other.d.in Other/Other.d COPYONLY)
configure_file(Other/Other.h.in Other/Other.h COPYONLY)
add_subdirectory(Other)
configure_file(Query/Query.d.in Query/Query.d COPYONLY)
configure_file(Query/Query.h.in Query/Query.h COPYONLY)
add_subdirectory(Query)
configure_file(Agents/Agents.d.in Agents/Agents.d COPYONLY)
configure_file(Agents/Agents.h.in Agents/Agents.h COPYONLY)
add_subdirectory(Agents)
configure_file(OnlineRender/OnlineRender.d.in OnlineRender/OnlineRender.d COPYONLY)
configure_file(OnlineRender/OnlineRender.h.in OnlineRender/OnlineRender.h COPYONLY)
add_subdirectory(OnlineRender)
add_subdirectory(UAS/Base)
add_subdirectory(UAS/MMDB)
add_subdirectory(UAS/DtSR)
add_subdirectory(Widgets)
add_subdirectory(cgm)
add_library(info_wwl STATIC
    wwl/src/WArgList.C
    wwl/src/WCallback.C
    wwl/src/WComposite.C
    wwl/src/WObject.C
    wwl/src/WXmList.C
    wwl/src/WXmMenu.C
    wwl/src/WXmRadioBox.C
    wwl/src/WXmString.C
)
target_link_libraries(info_wwl PUBLIC info_build_options)
add_library(dtinfo_impl INTERFACE)
target_link_libraries(dtinfo_impl INTERFACE info_build_options info_wwl)
target_sources(dtinfo_impl INTERFACE
    $<TARGET_OBJECTS:info_Support>
    $<TARGET_OBJECTS:info_Basic>
    $<TARGET_OBJECTS:info_OliasSearch>
    $<TARGET_OBJECTS:info_Marks>
    $<TARGET_OBJECTS:info_Graphics>
    $<TARGET_OBJECTS:info_Preferences>
    $<TARGET_OBJECTS:info_Managers>
    $<TARGET_OBJECTS:info_Other>
    $<TARGET_OBJECTS:info_Query>
    $<TARGET_OBJECTS:info_Agents>
    $<TARGET_OBJECTS:info_OnlineRender>
    $<TARGET_OBJECTS:info_UAS_Base>
    $<TARGET_OBJECTS:info_UAS_MMDB>
    $<TARGET_OBJECTS:info_UAS_DtSR>
    $<TARGET_OBJECTS:info_Widgets>
    $<TARGET_OBJECTS:info_cgm>
)
