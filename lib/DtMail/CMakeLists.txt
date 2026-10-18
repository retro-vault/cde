add_library(mail_build_options INTERFACE)
target_include_directories(mail_build_options INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/include/DtMail ${CMAKE_CURRENT_SOURCE_DIR}/include/MotifApp
    ${CMAKE_CURRENT_SOURCE_DIR}/Common ${CMAKE_CURRENT_SOURCE_DIR}/RFC)
target_link_libraries(mail_build_options INTERFACE cde_build_options DtSvc tt)
add_library(DtMail STATIC
    Common/APOPServer.C
    Common/AUTOServer.C
    Common/Buffer.C
    Common/DetermineFileLocality.C
    Common/DtMailBodyPart.C
    Common/DtMailEnvelope.C
    Common/DtMailError.C
    Common/DtMailMailBox.C
    Common/DtMailMessage.C
    Common/DtMailRc.C
    Common/DtMailServer.C
    Common/DtMailTransport.C
    Common/DtMailValuesBuiltin.C
    Common/DtMailXtProc.C
    Common/DtVirtArray.C
    Common/DynamicLib.C
    Common/FileShare.C
    Common/HashTable.C
    Common/IMAPServer.C
    Common/IO.C
    Common/LanguagePortability.C
    Common/ObjectKey.C
    Common/NotDynamic.C
    Common/POP2Server.C
    Common/POP3Server.C
    Common/Process.C
    Common/Session.C
    Common/Threads.C
    Common/md5.C
    Common/str_utils.C
    RFC/AliasExpand.C
    RFC/MIMEBodyPart.C
    RFC/MIMEPartial.C
    RFC/RFCBodyPart.C
    RFC/RFCEnvelope.C
    RFC/RFCFormat.C
    RFC/RFCMIME.C
    RFC/RFCMailBox.C
    RFC/RFCMailValues.C
    RFC/RFCMessage.C
    RFC/RFCTransport.C
    RFC/SunV3.C
    RFC/V3BodyPart.C
 )
target_link_libraries(DtMail PUBLIC mail_build_options)
target_compile_definitions(DtMail PRIVATE DL_NOT_DYNAMIC USE_SOCKSTREAM TTLOCK_OFF)
