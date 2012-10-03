#!/usr/bin/python

f=open("3.data","r").read()
for i in f:
    if ( i >= 'a' and i <= 'z' ) or (i >= 'A' and i <='Z'):
        print i
