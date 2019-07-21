#!/bin/bash

user=leiwang

if test $user
then
    echo "The $user exist"
else
    echo "The $user does not exits"
fi


if [ $user ]
then
    echo "The $user exist"
else
    echo "The $user does not exits"
fi

var1=5
var2=6

if [ $var1 -eq $var2 ]
then
    echo "var==var2"
else
    echo "var!=var2"
fi

user1=leiwang
user2=LeiWang
if [ $user1\>$user2 ]
then
    echo "$user1>$user2"
else
    echo "$user1<=$user2"
fi

