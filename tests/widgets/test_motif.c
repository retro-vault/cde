#include <Xm/PushB.h>
int main(int argc, char **argv)
{
    XtAppContext app;
    Widget shell = XtVaAppInitialize(&app, "MotifTest", NULL, 0,
                                     &argc, argv, NULL, NULL);
    Widget button = XmCreatePushButton(shell, "button", NULL, 0);
    XtManageChild(button);
    XtRealizeWidget(shell);
    XSync(XtDisplay(shell), False);
    XtDestroyWidget(shell);
    XtDestroyApplicationContext(app);
    return 0;
}
