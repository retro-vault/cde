add_executable(ttdbck
    binkey.C
    binkey_utils.C
    common.C
    options.C
    options_tt.C
    prop.C
    prop_utils.C
    spec.C
    spec_repair.C
    spec_utils.C
    ttdbck.C
)
target_include_directories(ttdbck PRIVATE ${PROJECT_SOURCE_DIR}/lib/tt/slib)
target_link_libraries(ttdbck PRIVATE tt_server tt_isam tt tt_build_options)
install(TARGETS ttdbck RUNTIME DESTINATION bin)
