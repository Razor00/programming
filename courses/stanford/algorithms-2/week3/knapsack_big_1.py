#!/usr/bin/python
import sys

def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)


def knapsack(sack, size, n):
    M = [0 for i in range(size+1)]
    gcd_all = size
    for i in range(1, n+1):
        gcd_all = gcd(gcd_all, sack[i][1])
    for i in range(1, n+1):
        sack[i][1] = sack[i][1]/gcd_all

    size = size/gcd_all
    print gcd_all
    for i in range(1, n+1):
        for w in xrange(size, 1, -1):
            v_i = sack[i][0]
            w_i = sack[i][1]
            v = M[w]
            if w_i <= w:
                v = max(M[w], M[w-w_i] + v_i)
            M[w] = v
        print i
    print M[size]*gcd_all


def compare(a, b):
    return a[1]-b[1]


f = open(sys.argv[1], "r")
size, nitems =  map(int, next(f).rstrip("\r\n").split())
print size, nitems

ksack=[(0,0) for i in range(nitems+1)]
for i in range(1, nitems+1):
    ksack[i] = map(int, next(f).rstrip("\r\n").split())
#print ksack
ksack.sort(cmp=compare)
print ksack
knapsack(ksack, size, nitems)
