#!bin/bash
#测试参数的总数
if [ $# -ne 2 ]
then
    echo
    echo Usage: test1.sh a b
    echo
else
    total=$[ $1+$2 ]
    echo
    echo The total is $total
    echo
fi
