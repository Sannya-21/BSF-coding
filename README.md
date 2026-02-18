# Graph-Based Collaboration Path Finder (C++ | BFS | Graphviz)

##  Project Overview

This project implements a Graph-Based Collaboration Analysis System using C++.  
It models relationships between professional roles and projects as an undirected graph and uses the Breadth-First Search (BFS) algorithm to compute the shortest collaboration path between roles.


---

##  Features

- Object-Oriented Design (Node & Graph classes)
- Graph implementation using Adjacency List
- Breadth-First Search (BFS) algorithm
- Shortest path reconstruction using parent tracking
- Automatic Graph Visualization using Graphviz
- Shortest path highlighted in red
- Console-based user interaction

---

##  Technologies Used

- C++
- STL (vector, queue, unordered_map, set)
- Graphviz (for visualization)

---

##  Project Structure

main.cpp  
graph.dot  
graph.png  
README.md  

---

## ⚙️ How It Works

1. Builds a graph of:
   - Projects
   - Professional roles

2. Each project connects to associated roles.

3. User enters a starting role.

4. BFS finds the shortest path to:
   System Architect

5. The program:
   - Prints the shortest collaboration path
   - Exports graph to .dot format
   - Automatically generates graph.png

---


## 🖼 Visualization

After running, the program generates:

graph.png

The graph shows:
- All nodes (projects & roles)
- All connections
- Shortest path highlighted in red

---

##  Algorithm Used

Breadth-First Search (BFS)

BFS guarantees the shortest path in an unweighted graph.

Time Complexity:
O(V + E)

Space Complexity:
O(V)



##  Academic Relevance

This project demonstrates:

- Graph Data Structures
- BFS Traversal
- Path Reconstruction
- Real-world modeling using graphs
- Visualization using external tools

Suitable for:
Data Structures course 

---




##  Author

sannya jan  
