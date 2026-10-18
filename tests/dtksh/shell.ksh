set -e
[[ $((1 << 40)) == 1099511627776 ]]
typeset -a items=(alpha beta gamma)
[[ ${items[1]} == beta ]]
typeset -A mapping=([key]=value)
[[ ${mapping[key]} == value ]]
function compute { typeset -i local_value=7; print $((local_value * 6)); }
[[ $(compute) == 42 ]]
[[ $(printf '%s:%d' answer 42) == answer:42 ]]
whence XtInitialize > /dev/null
