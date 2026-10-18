set -e
XtInitialize TOPLEVEL cdeTest CdeTest "$0"
XmCreateTextField FIELD "$TOPLEVEL" field value:"native CMake"
XtManageChild "$FIELD"
XtRealizeWidget "$TOPLEVEL"
XmTextFieldGetString VALUE "$FIELD"
[[ $VALUE == "native CMake" ]]
XtDestroyWidget "$TOPLEVEL"
