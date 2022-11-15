import sys
from math import factorial

sys.setrecursionlimit(1000001)


def dfs(node, tree):
    tree_perms = 1
    if tree[node] and node != 0:
        tree_perms = factorial(len(tree[node]) + 1)
    for child in tree[node]:
        tree_perms *= dfs(child, tree)
    return tree_perms


def main():
    n = int(input())
    connections = [int(i) for i in input().split()]
    tree = []
    tree.append([])
    for child, parent in enumerate(connections):
        tree.append([])
        tree[parent - 1].append(child + 1)
    answer = n * factorial(len(tree[0])) * dfs(0, tree)
    print(answer % (10 ** 9 + 7))


if __name__ == "__main__":
    main()
