#!/usr/bin/python


def isupper(ch):
    if ch >='A' and ch <= 'Z':
        return 1
    else:
        return 0

def islower(ch):
    if ch >='a' and ch <= 'z':
        return 1
    else:
        return 0


import sys

if len(sys.argv) != 2:
    print "Please enter filename"
    sys.exit(0)

fname=sys.argv[1]
f=open(fname,"r").read()
flen=len(f)

i=0
while i < flen:
	if islower(f[i]) and islower(f[i+8]) and islower(f[i+4]):
		if isupper(f[i+1]) and isupper(f[i+2]) and isupper(f[i+3]):
			if isupper(f[i+5]) and isupper(f[i+6]) and isupper(f[i+7]):
				print f[i+1],f[i+2],f[i+3],f[i+4],f[i+5],f[i+6],f[i+7]
				print i
	i=i+1

