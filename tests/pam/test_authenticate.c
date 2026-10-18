#include <Dt/SvcPam.h>
#include <security/pam_appl.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    struct passwd *account = getpwuid(getuid());
    const char *service = "cde-port-test";
    if (account == NULL) {
        return 1;
    }
    if (_DtSvcPamAuthenticate(service, account->pw_name, ":0", "test-only-password") != PAM_SUCCESS) {
        fprintf(stderr, "PAM rejected the two-message conversation\n");
        return 1;
    }
    if (_DtSvcPamAuthenticate(service, "cde-test-other-identity", ":0", "test-only-password") == PAM_SUCCESS) {
        fprintf(stderr, "PAM reused the previous identity\n");
        return 1;
    }
    if (_DtSvcPamAuthenticate(service, account->pw_name, ":0", "incorrect") == PAM_SUCCESS) {
        fprintf(stderr, "PAM accepted an incorrect password\n");
        return 1;
    }
    if (_DtSvcPamAuthenticate(service, account->pw_name, ":0", "test-only-password") != PAM_SUCCESS ||
        _DtSvcPamSetcred(service, account->pw_name, ":0") != PAM_SUCCESS ||
        _DtSvcPamOpenSession(service, account->pw_name, ":0") != PAM_SUCCESS ||
        _DtSvcPamCloseSession(service, account->pw_name, ":0") != PAM_SUCCESS) {
        fprintf(stderr, "PAM could not reuse the handle for a valid session\n");
        return 1;
    }
    if (_DtSvcPamAccountManagement(service, account->pw_name, ":0") != PAM_SUCCESS ||
        _DtSvcPamAccountManagement("cde-port-test-denied", account->pw_name, ":0") == PAM_SUCCESS) {
        fprintf(stderr, "PAM account policy was ignored\n");
        return 1;
    }
    return 0;
}
