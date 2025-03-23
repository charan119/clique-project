# Maximal Clique Enumeration Algorithms

## Project Overview

This repository contains implementations of three classical maximal clique enumeration algorithms:
- **Tomita et al.'s algorithm**
- **Eppstein et al.'s degeneracy-based algorithm**
- **Chiba and Nishizeki's arboricity-based algorithm**

The project focuses on comparing the performance of these algorithms on real-world network datasets of varying sizes. Maximal clique enumeration is a fundamental problem in graph theory with applications in social network analysis, bioinformatics, and data mining. A clique is a subset of vertices of a graph where every two distinct vertices are connected by an edge; a maximal clique is one that cannot be extended by including any adjacent vertex.

## Repository Structure

This repository consists of six C++ files:
- `graph.h` – Header file containing graph data structure definitions.
- `graph.cpp` – Implementation of graph loading and utility functions.
- `tomita.cpp` – Implementation of Tomita et al.'s algorithm.
- `eppstein.cpp` – Implementation of Eppstein et al.'s degeneracy-based algorithm.
- `chiba.cpp` – Implementation of Chiba and Nishizeki's arboricity-based algorithm.
- `main.cpp` – Main program that coordinates the execution of all algorithms.

## Installation and Setup

1. **Clone the repository:**
[git clone https://github.com/charan119/clique-project/]
cd clique-project


2. **Download the datasets:**

Download the following dataset files from our [Google Drive folder](https://drive.google.com/drive/folders/1z9flRqQRqU7CosIcEVFItG1IJpvPN0xO?usp=sharing):
- `Email-Enron.txt`
- `Wiki-Vote.txt`
- `as-skitter.txt`

Place the downloaded files in the same folder as the source code.

3. **Compile the program:**

Use the following command (assuming you have a C++ compiler like g++ installed):
`g++ -O3 -std=c++11 main.cpp graph.cpp tomita.cpp eppstein.cpp chiba.cpp -o maximal_cliques`


## Usage

Run the program with one of the dataset files as a command-line argument:

For the Wiki-Vote dataset (smallest)
`maximal_cliques.exe Wiki-Vote.txt`

For the Email-Enron dataset (medium)
`maximal_cliques.exe Email-Enron.txt`

For the as-skitter dataset (largest)
`maximal_cliques.exe as-skitter.txt`


The program will:
1. Load the graph from the specified file.
2. Run all three maximal clique enumeration algorithms and measure each algorithm's execution time.
3. Report the number of maximal cliques found by each algorithm.
4. Provide an analysis of the clique size distribution.

## Datasets

The project uses three real-world network datasets sourced from the Stanford Network Analysis Project (SNAP):

- **Wiki-Vote:** Wikipedia voting network with 7,115 nodes and 103,689 edges.
- **Email-Enron:** Email communication network from Enron with 36,692 nodes and 183,831 edges.
- **as-Skitter:** Internet topology graph (traceroutes) with 1,696,415 nodes and 11,095,298 edges.

All datasets are available in our [Google Drive folder](https://drive.google.com/drive/folders/1z9flRqQRqU7CosIcEVFItG1IJpvPN0xO?usp=sharing).

## Team Members and Individual Contributions

Our team consists of five members, each contributing to different aspects of the project:

1. **Kasina Sahiti:**
   - Implemented the Tomita et al. algorithm (`tomita.cpp`).
   - Assisted with the graph loading functionality.
   - Conducted performance analysis for small datasets.

2. **Valavala Charan Teja:**
   - Implemented the Eppstein et al. algorithm (`eppstein.cpp`).
   - Designed and optimized the degeneracy ordering computation.
   - Performed performance tuning for medium-sized datasets.

3. **Saksham Daga:**
   - Implemented the Chiba and Nishizeki algorithm (`chiba.cpp`).
   - Created the time constraint mechanism for large datasets.
   - Documented algorithm complexity analysis.

4. **Kunal:**
   - Developed the graph data structures and utilities (`graph.h`, `graph.cpp`).
   - Implemented the main integration of the project (`main.cpp`).
   - Ensured cross-platform compatibility.

5. **Aryan Saini:**
   - Performed experimental evaluation and analysis.
   - Created visualizations of the results.
   - Developed the project website.
   - Coordinated documentation and project management.

## Project Website

For detailed experimental results, visualizations, and more information about this project, please visit our [project website](https://charan119.github.io/).

## Project Repository
 [project repo]([https://github.com/charan119/clique-project]).
