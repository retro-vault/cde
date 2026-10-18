add_library(mmdb_dti_cc OBJECT
    CC_Dlist.C
    CC_Listbase.C
    CC_Slist.C
    CC_Stack.C
    CC_String.C
    CC_Tokenizer.C
    cc_exceptions.C
    cc_hdict.C
    cc_povec.C
    cc_pvect.C
    cc_vvect.C
    hdictinit.C
    vectinit.C
)
target_link_libraries(mmdb_dti_cc PRIVATE mmdb_build_options)
set_target_properties(mmdb_dti_cc PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(mmdb_dti_cc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
