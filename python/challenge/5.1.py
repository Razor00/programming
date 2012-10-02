#!/usr/bin/python
import sys
import urllib2
import re
count=0
#http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=16044
id=16044/2
while count < 400:
    myurl='http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=%s' % (id)
    print myurl
    response = urllib2.urlopen(myurl)
    html = response.read()
    id=re.search('next nothing is (\d+)', html).groups()
    print id
    count=count+1

#ans: peak.html
