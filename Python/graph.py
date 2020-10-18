#!/bin/python3

import os

N = 7
a = [[0] * N for i in range(N)]

def print_matrix():
    for i in range(0, N):
        for j in range(0, N):
            print(a[i][j], end = ' ')
        print()

def add_edge(u, v):
    a[u][v] = 1
    #a[v][u] = 1

def BFS(i):
    queue = []
    visited = []

    queue.insert(0, i)
    visited.append(i)
    while(len(queue) > 0):
        n = queue.pop(0)
        for j in range(0, N):
            if (a[n][j] == 1) and visited.count(j) == 0:
                queue.insert(0, j)
                visited.append(j)
    print(visited)

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
    add_edge(2, 6)
    add_edge(0, 3)
    add_edge(1, 4)
    add_edge(4, 5)
    print_matrix()
    print("BFS")
    BFS(0)

    print("DFS_I")
    DFS_I(0)

    print("DFS")
    DFS(0)
