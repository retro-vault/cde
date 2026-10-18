#include <Dt/Control.h>
#include <Xm/BulletinB.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    XtAppContext app;
    Widget shell;
    Widget board;
    Widget mail;
    String filename = NULL;
    struct passwd *user;
    int result = EXIT_FAILURE;

    unsetenv("LOGNAME");
    unsetenv("MAIL");
    shell = XtVaAppInitialize(&app, "CdeTest", NULL, 0, &argc, argv, NULL, NULL);
    board = XmCreateBulletinBoard(shell, "board", NULL, 0);
    mail = XtVaCreateManagedWidget("mail", dtControlGadgetClass, board,
        "controlType", XmCONTROL_MAIL, "alternateImage", "missing-test-image", NULL);
    XtVaGetValues(mail, "fileName", &filename, NULL);
    user = getpwuid(getuid());
    if (filename != NULL) {
        if (user == NULL) {
            result = filename[0] == '\0' ? EXIT_SUCCESS : EXIT_FAILURE;
        } else if (strncmp(filename, "/var/mail/", 10) == 0 &&
                   strcmp(filename + 10, user->pw_name) == 0) {
            result = EXIT_SUCCESS;
        }
    }
    if (result != EXIT_SUCCESS) {
        fprintf(stderr, "Mail control failed to choose an account fallback\n");
    }
    XtDestroyWidget(shell);
    XtDestroyApplicationContext(app);
    return result;
}
