#include <Dt/Editor.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    XtAppContext app;
    Widget shell = XtVaAppInitialize(&app, "CdeTest", NULL, 0,
                                     &argc, argv, NULL, NULL);
    Widget editor = DtCreateEditor(shell, "editor", NULL, 0);
    DtEditorContentRec input = {.type = DtEDITOR_TEXT};
    DtEditorContentRec output = {.type = DtEDITOR_TEXT};
    int result = EXIT_FAILURE;

    XtManageChild(editor);
    XtRealizeWidget(shell);
    input.value.string = "CDE on 64-bit Linux\nsecond line\n";
    if (DtEditorSetContents(editor, &input) == DtEDITOR_NO_ERRORS &&
        DtEditorGetContents(editor, &output, False, True) == DtEDITOR_NO_ERRORS) {
        if (strcmp(input.value.string, output.value.string) == 0) {
            result = EXIT_SUCCESS;
        }
        XtFree(output.value.string);
    }
    if (result != EXIT_SUCCESS) {
        fprintf(stderr, "Editor text round trip failed\n");
    }
    XtDestroyWidget(shell);
    XtDestroyApplicationContext(app);
    return result;
}
