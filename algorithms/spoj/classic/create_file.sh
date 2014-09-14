#!/bin/bash

if [ "x$1" = "x" ]; then
    echo "$0 op_file"
    exit 0
fi
cat| fmt -w 80 > /tmp/.file 
echo "*/
#include <stdio.h>
int main()
{
    int t;
    scanf(\"%d\", &t);
    while (t--){
    }
    return 0;
}
">>/tmp/.file
cp /tmp/.file $1
