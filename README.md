# Binary Search Tree

A modern C++ implementation of a Binary Search Tree (BST) used to sort 10,000 random numbers in the range `[0; 1.000.000]` using the Tree Sort algorithm.


## Build
Requires ``g++`` and ``make``.

```sh
git clone https://github.com/ohSystemmm/binary-search-tree.git
cd ip-subnet-calc
make run
```
On Windows this creates binary_search_tree.exe.  
On Linux/macOS it creates binary_search_tree.

## Usage

```sh
# Windows
./binary_search_tree.exe 

# Linux/macOS
./binary_search_tree
```

## Complexity Analysis
| Operation | Average Case | Worst Case (Unbalanced) |
| :--- | :--- | :--- |
| **Insertion ($N$ items)** | $O(N \log N)$ | $O(N^2)$ |
| **In-Order Traversal** | $O(N)$ | $O(N)$ |
| **Total Sort Time** | $O(N \log N)$ | $O(N^2)$ |
| **Space Complexity** | $O(U)$ where $U \le N$ is unique elements | $O(N)$ |