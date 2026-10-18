#include "dm.h"
#include "sysauth.h"
#include <pwd.h>
#include <unistd.h>

char *progName = "cde-port-test";

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    struct passwd *account = getpwuid(getuid());
    struct display display = {0};
    char password[] = "test-only-password";
    char incorrect[] = "incorrect";
    char *message = NULL;
    display.name = ":0";
    if (account == NULL) {
        return 1;
    }
    if (Authenticate(&display, account->pw_name, password, &message) != VF_OK ||
        Authenticate(&display, account->pw_name, incorrect, &message) != VF_INVALID ||
        Authenticate(&display, NULL, password, &message) != VF_INVALID) {
        fprintf(stderr, "Login manager did not enforce password authentication\n");
        return 1;
    }
    progName = "cde-port-test-denied";
    if (Authenticate(&display, account->pw_name, password, &message) != VF_INVALID) {
        fprintf(stderr, "Login manager ignored PAM account denial\n");
        return 1;
    }
    return 0;
}
