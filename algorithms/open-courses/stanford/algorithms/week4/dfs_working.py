#!/usr/bin/python
import sys
sys.setrecursionlimit(10**9)
import threading
threading.stack_size(67108864)

depth = 0
def dfs(Grev, visited, v, order1, order2):
    global number
#    global depth
    visited[v] = True
    for e in Grev[v]:
        if not visited[e]:
#            depth += 1
#            if depth % 1000 == 0:
#                print "recursion depth\n", depth
#                print "Lenth of visited nodes : ", len(visited)
            dfs(Grev, visited, e, order1, order2);
#            depth -= 1
    number = number + 1
    order1[v] = number 
    order2[number] = v
    #print v, number
    return 0

def dfs1(G, visited, v, order1, order2, n):
    visited[v] = True
    #print v, order2[v]
    for e in G[order2[v]]:
        if not visited[order1[e]]:
            n = dfs1(G, visited, order1[e], order1, order2, n)  + 1;
    return n

f = open(sys.argv[1], 'r')
max_v = int(f.readline().rstrip('\n\r'));
N = int(f.readline().rstrip('\n\r'));
print N

G={}
Grev={}
order1={}
order2={}
visited={}
for i in range(max_v+1):
    G[i]        = []
    Grev[i]     = []
    order1[i]   = []
    order2[i]   = []
    visited[i]  = False


for i in range(N):
    v = map(int, f.readline().split())
    s = v.pop(0)
    d = v.pop(0)
    if s != d:
        G[s].extend([d]);
        G[s] = list(set(G[s]))
        Grev[d].extend([s])
        Grev[d] = list(set(Grev[d]))
print "Graph reading done"
#===============Stage 1=============
#print G
#print Grev
number=0
i = 1
for v in range(len(G)-1, 0, -1):
    if not visited[v]:
        dfs(Grev, visited, v, order1, order2) 
#       print "processed vertex", v

#print "Order1:",  order1, len(order1)
#print  "Order2:", order2


#===============Stage 2================
for i in range(max_v+1):
    visited[i] = False
leader={}
number=0
for v in range(len(G)-1, 0, -1):
    if not visited[v]:
        if v not in leader:
            leader[v] = []
        leader[v] = dfs1(G, visited, v, order1, order2, 1) 
print leader


import operator
print sorted(leader.iteritems(), key=operator.itemgetter(1), reverse=True)[:5]

