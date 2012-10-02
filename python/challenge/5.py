#!/usr/bin/python
import sys
import urllib2
import re
count=0
id=12345
while count < 400:
    myurl='http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=%s' % (id)
    print myurl
    response = urllib2.urlopen(myurl)
    html = response.read()
    id=re.search('(\d+)', html).groups()
    print id
    count=count+1
