#!/usr/bin/python


def get_pivot1(st, end):
    return st

def get_pivot2(st, end):
    return end


def get_pivot3(st, end):
    return 0

def print_data(arr, pivot):
    print "%s, %s" % (st, end)
    print pivot
    print arr

def partition(arr, p, st, end):
    arr[p], arr[st] = arr[st], arr[p]
    arr_p = arr[st]
    i = j = st+1
    print arr
    while i <= j and j <= end:
        while i <= end and arr[i] < arr_p:
                i = i+1
        while j <= end and arr[j] > arr_p:
                j = j+1
        if i < j and j <= end:
            arr[i], arr[j] = arr[j], arr[i]
#        print i, ",", j, "-", arr
        i += 1
        j += 1
    i = i - 2
    arr[st], arr[i] = arr[i], arr[st]
    print_data(arr, p)

def qsort(array, st, end):
    if end <= st:
        return 0
    print "%s, %s" % (st, end)
    pivot = get_pivot1(st, end) 
    partition(array, pivot, st, end)
    sz = end - st + 1
    lt = qsort(array, st, pivot-1)
    rt = qsort(array, pivot+1, end)
    return lt + rt + sz




f = open('input.txt', 'r')

N = int(f.readline().rstrip());

array = [int(x.rstrip('\n\r')) for x in f]

inversions = 0
#partition(array, 4, 0, N-1)
print qsort(array, 0, N-1)

