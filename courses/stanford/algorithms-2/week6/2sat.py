#!/usr/bin/python


import math
import sys


f = open(sys.argv[1], "r")
max_clause = max_var = int(f.readline().rstrip())

positive_var  = {i:[-1, 0] for i in range(0, max_var+1)}
negative_var  = {i:[-1, 0] for i in range(0, max_var+1)}
clauses       = {i:[-1] for i in range(0, max_var+1)}
for i, line in enumerate(f):
    clause = map(int, line.rstrip().split())
    clauses[i] = clause
    for v in clause:
        if v < 0:
            negative_var[abs(v)][1] += 1
            negative_var[abs(v)].append(i)
        if v >= 0:
            positive_var[v][1] += 1
            positive_var[v].append(i)
prev = len(clauses)-1
while True:
    for k in positive_var.keys():
        if positive_var[k][0] == -1 and negative_var[k][1] == 0:
            positive_var[k][1] = 0
            positive_var[k][0] = 1
            for c in positive_var[k][1:]:
                if c in clauses:
                    ov = clauses[c][0]
                    if ov == k:
                        ov = clauses[c][1]
                    del (clauses[c])
                    if ov < 0:
                        negative_var[abs(ov)][1] -= 1
                    else:
                        positive_var[abs(ov)][1] -= 1
        
#        print len(clauses)

    for k in negative_var.keys():
#        print k
#        print negative_var[k]
        if negative_var[k][0] == -1 and positive_var[k][1] == 0:
            negative_var[k][1] = 0
            negative_var[k][0] = 1
            for c in negative_var[k][1:]:
                if c in clauses:
                    ov = clauses[c][0]
                    if ov == -k:
                        ov = clauses[c][1]
                    del (clauses[c])
                    if ov < 0:
                        negative_var[abs(ov)][1] -= 1
                    else:
                        positive_var[abs(ov)][1] -= 1
    print len(clauses)-1
    if prev == len(clauses)-1:
        sys.exit()
    prev = len(clauses)-1
    if len(clauses) == 1926:
        print clauses
        print "positives"
        print negative_var
        print "negatives"
        print positive_var
        raw_input()

