#!/usr/bin/python

def euler_tour(G,V):
    tour = []
    (e1, e2) = G.pop(0)
    V[e1].remove(e2)
    V[e2].remove(e1)
    tour.append(e1)
    tour.append(e2)
    v = e2

    while G:
        if len(V[v]) > 0:
            e2 = V[v][0]
            e1, v = v, e2
            if (e2, e1) in G:
                e1, e2 = e2, e1
            G.remove((e1, e2))
        else:
            break 
        V[e1].remove(e2)
        V[e2].remove(e1)
        tour.append(v)
    return tour


def euler_tour1(G, V):

    tour=[]
    (e1, e2) = G.pop(0)
    V[e1].remove(e2)
    V[e2].remove(e1)
    tour.append(e1)
    tour.append(e2)
    v = e2
    while G:
        if len(V[v]) > 0:
            e2 = V[v][0]
            e1, v = v, e2
            if (e2, e1) in G:
                e1, e2 = e2, e1
            G.remove((e1, e2))
        else:
            (e1, e2) = G.pop(0)
            tour.append(e1)
            v = e2
            if (e1, e2) == (3, 4):
                print "found"
                print G
        V[e1].remove(e2)
        V[e2].remove(e1)
        tour.append(v)

    print tour
    print G



def find_eulerian_tour(G):
    V={}
    for e in G:
        if e[0] not in V:
            V[e[0]] = []
        if e[1] not in V:
            V[e[1]] = []

        V[e[0]].append(e[1])
        V[e[0]] = list(set(V[e[0]]))
        V[e[1]].append(e[0])
        V[e[1]] = list(set(V[e[1]]))
        
    Gtour = []
    tour = []
    while G:
        tour = euler_tour(G, V)
        print tour
        if Gtour:
            v = list(set(tour) & set(Gtour))
            if Gtour and v[0] in Gtour:
                pos_g = Gtour.index(v[0])
                pos_t = tour.index(v[0])
                t_tour = tour[pos_t+1:] + tour[1:pos_t+1]
                print t_tour
                i = 1
                for j in t_tour:
                    Gtour.insert(pos_g+i, j)
                    i += 1
        else:
            Gtour.extend(tour)
    print Gtour

#G=[(1,2),(1,3),(1,5),(1,6),(2,3),(2,4),(2,6),(3,4),(3,6),(4,5),(4,6)]
G = [(1, 13), (1, 6), (6, 11), (3, 13),
 (8, 13), (0, 6), (8, 9),(5, 9), (2, 6), (6, 10), (7, 9),
 (1, 12), (4, 12), (5, 14), (0, 1),  (2, 3), (4, 11), (6, 9),
 (7, 14),  (10, 13)]
find_eulerian_tour(G)
