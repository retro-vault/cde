install(FILES
    ${PROJECT_BINARY_DIR}/include/Dt/Dt.h Dt/Action.h Dt/Dnd.h Dt/Dts.h Dt/Session.h Dt/Saver.h Dt/Wsm.h
    Dt/MsgLog.h Dt/Info.h Dt/Editor.h Dt/ComboBox.h Dt/SpinBox.h Dt/MenuButton.h
    Dt/HelpDialog.h Dt/Help.h Dt/HelpQuickD.h Dt/Print.h Dt/TermPrim.h Dt/Term.h
    Dt/Mrm.h Dt/Search.h Dt/Mmdb.h DESTINATION include/Dt)
if(TARGET PAM::PAM)
    install(FILES Dt/SvcPam.h DESTINATION include/Dt)
endif()
