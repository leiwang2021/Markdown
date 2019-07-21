#!/bin/bash
#test if-then

testuser=leiwang
if grep $testuser /etc/passwd
then
    echo "This is ma first command"
    ls -a /home/$testuser/.b*

fi
