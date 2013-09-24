#!/usr/bin/python
import sys



def knapsack(sack, size, n):
    M0 = [0 for i in range(size+1)]
    M1 = [0 for i in range(size+1)]
    for i in range(1, n+1):
        for w in range(size+1):
            v_i = sack[i][0]
            w_i = sack[i][1]
            v = M0[w]
            if w_i <= w:
                v = max(M0[w], M0[w-w_i] + v_i)
            M1[w] = v
        print i
        M0, M1 = M1, M0
    print M0[size]





f = open(sys.argv[1], "r")
size, nitems =  map(int, next(f).rstrip("\r\n").split())
print size, nitems

ksack=[(0,0) for i in range(nitems+1)]
for i in range(1, nitems+1):
    ksack[i] = map(int, next(f).rstrip("\r\n").split())
#print ksack

knapsack(ksack, size, nitems)
