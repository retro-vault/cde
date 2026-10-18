add_library(tt_tttk OBJECT
    ttdesktop.C
    ttdtfile.C
    ttdtprocid.C
    ttmedia.C
    tttk.C
    tttk2free.C
    tttkmessage.C
    tttkpattern.C
    tttkutils.C
)
target_link_libraries(tt_tttk PRIVATE tt_build_options)
set_target_properties(tt_tttk PROPERTIES POSITION_INDEPENDENT_CODE ON)
