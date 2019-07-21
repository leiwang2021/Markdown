#!/bin/bash
#test if-then

testuser=leiwang2021
if grep $testuser /etc/passwd
then
    echo "This is ma first command"
    ls -a /home/$testuser/.b*
fi
exit 6
