#!/bin/bash
#testing $*  $@
echo
cout=1
for param in "$*"
do
    echo "\$* Parameter #$count=$param"
    count=$[ $count+1 ]
done

echo
count=1
for param in "$@"
do
    echo "\$@ Parameter #$count=$param"
    count=$[ $count+1 ]
done
