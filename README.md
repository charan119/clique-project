# Maximal Clique Enumeration Project

This project implements and compares three maximal clique enumeration algorithms—Tomita, Eppstein, and Chiba—on the Wiki-Vote and Email-Enron datasets.

## Execution Instructions
1. **Compile**: `g++ -o clique_enum src/main.cpp`
2. **Run**: `./clique_enum <dataset_file>`
   - Example: `./clique_enum data/wiki-vote.txt`
3. **Dependencies**: Standard C++ libraries (no external dependencies).

## Dataset Preparation
- **Source**: Datasets are available from [SNAP](http://snap.stanford.edu/data/).
  - Wiki-Vote: `Wiki-Vote.txt`
  - Email-Enron: `Email-Enron.txt`
  - As-Skitter: 
- **Format**: One edge per line (node1 node2).
- **Preprocessing**: The code converts directed edges to undirected and maps vertices to 0-based indices.

## Individual Contributions
- [Your Name]: Algorithm implementation, data processing, experiments, visualizations, and report writing.

## Project Webpage
- [View the project webpage](https://username.github.io/clique-project) (update this link after Step 4).
