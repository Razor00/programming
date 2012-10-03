#!/usr/bin/python
import re
f=open("3.data","r").read()
for match in re.finditer('[a-z][A-Z]{3}([a-z])[A-Z]{3}[a-z]', f):
    print match.groups()

