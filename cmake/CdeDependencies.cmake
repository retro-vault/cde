find_library(CRYPT_LIBRARY crypt REQUIRED)
find_path(MOTIF_INCLUDE_DIR Xm/Xm.h REQUIRED)
find_library(MOTIF_LIBRARY Xm REQUIRED)
find_library(MRM_LIBRARY Mrm REQUIRED)
find_path(PAM_INCLUDE_DIR security/pam_appl.h)
find_library(PAM_LIBRARY pam)
add_library(Motif::Xm UNKNOWN IMPORTED)
set_target_properties(Motif::Xm PROPERTIES IMPORTED_LOCATION "${MOTIF_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${MOTIF_INCLUDE_DIR}")
if(PAM_INCLUDE_DIR AND PAM_LIBRARY)
    add_library(PAM::PAM UNKNOWN IMPORTED)
    set_target_properties(PAM::PAM PROPERTIES IMPORTED_LOCATION "${PAM_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${PAM_INCLUDE_DIR}")
endif()
add_library(cde_build_options INTERFACE)
target_include_directories(cde_build_options INTERFACE
    ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/include/Dt
    ${PROJECT_SOURCE_DIR}/include/Tt ${PROJECT_BINARY_DIR}/include)
target_compile_definitions(cde_build_options INTERFACE
    _GNU_SOURCE _POSIX_C_SOURCE=200809L HAVE_CONFIG_H
    MULTIBYTE NLS16 I18N_MSG
    CDE_INSTALLATION_TOP="${CDE_INSTALLATION_TOP}" CDE_DATA_TOP="${CDE_DATA_TOP}"
    CDE_CONFIGURATION_TOP="${CDE_CONFIGURATION_TOP}" CDE_LOGFILES_TOP="${CDE_LOGFILES_TOP}"
    CDE_LIBEXEC_DIR="${CDE_LIBEXEC_DIR}")
target_compile_options(cde_build_options INTERFACE -Wall -Wextra
    $<$<COMPILE_LANGUAGE:C>:-Werror=implicit-function-declaration;-Werror=int-to-pointer-cast;-Werror=pointer-to-int-cast>)
target_link_libraries(cde_build_options INTERFACE
    cde_private_headers
    # Motif interposes Xt vendor-shell symbols. Keep it ahead of libXt even
    # when a client calls only CDE APIs and the linker uses --as-needed.
    -Wl,--push-state,--no-as-needed Motif::Xm -Wl,--pop-state X11::Xt X11::X11 X11::Xext X11::Xmu X11::Xpm X11::SM X11::ICE)
