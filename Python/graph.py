#!/bin/python3

import os

N = 7
a = [[0] * N for i in range(N)]

def enqueue(q, i):
    q.append(i)

def dequeue(q):
    return q.pop(0)

def push(s, i):
    s.append(i)

def pop(s):
    return s.pop(len(s)-1)

def print_matrix():
    for i in range(0, N):
        for j in range(0, N):
            print(a[i][j], end = ' ')
        print()

def add_edge(u, v):
    a[u][v] = 1
    #a[v][u] = 1

def BFS(i):
    q = []
    visited = []

    enqueue(q, i)
    visited.append(i)
    while(len(q) > 0):
        n = dequeue(q)
        for j in range(0, N):
            if ( a[n][j] == 1) and visited.count(j) == 0:
                enqueue(q,j)
                visited.append(j)
    print(visited)

def BFS_path(s, e):
    queue = []
    dist = [-1 for i in range(N)]

    enqueue(queue, s)
    while(len(queue) > 0):
        n = dequeue(queue)
        for j in range(0, N):
            if ( a[n][j] == 1):
                if dist[j] == -1:
                    enqueue(queue, j)
                    dist[j] = dist[n]+1
    print(dist)
    return dist[e]

def DFS_path(s, e):
    stack = []
    dist = [-1 for i in range(N)]

    push(stack, s)
    while(len(stack) > 0):
        n = pop(stack)
        for j in range(0, N):
            if ( a[n][j] == 1):
                if dist[j] == -1:
                    push(stack, s)
                    stack.insert(len(stack), j)
                    dist[j] = dist[n]+1
    print(dist)
    return dist[e]

def DFS_I(i):
    stack = []
    visited = []

    stack.insert(len(stack), i)
    while(len(stack) > 0):
        n = stack.pop(len(stack)-1)
        visited.append(n)
        for j in reversed(range(0, N)):
            if (a[n][j] == 1) and visited.count(j) == 0:
                stack.insert(len(stack), j)
                print("inserting " + str(j))

    print(visited)

def DFS_helper(i, visited):
    if (visited.count(i)):
        return
    visited.append(i)
    for j in range(0, N):
        if (a[i][j] == 1):
            DFS_helper(j, visited)

def DFS(i):
    visited = []
    DFS_helper(i, visited)
    print(visited)

if __name__ == "__main__":
    add_edge(0, 1)
    add_edge(0, 2)
    add_edge(0, 3)
    add_edge(0, 4)
    add_edge(4, 5)

    print_matrix()
    print("BFS")
    BFS(0)

    print("DFS_I")
    DFS_I(0)

    print("DFS")
    DFS(0)

    print("BFS path 0 -> 4")
    ret = BFS_path(0, 5)
    print(ret + 1)
    print("DFS path 0 -> 4")
    ret = DFS_path(0, 5)
    print(ret + 1)