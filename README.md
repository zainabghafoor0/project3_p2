# Huffman Coding Project — Phase 2

## Overview
This phase extends **Part 1** of the Huffman project by adding two new data structures and producing measurable artifacts that will later support encoding.

Given an input text file, the program:

1. **Tokenizes** it using the existing `Scanner` module (from Part 1).  
2. Builds a **Binary Search Tree (BST)** to compute word frequencies.  
3. Constructs a **simulated Priority Queue** using a sorted vector.  

The program then outputs:
- A `.tokens` file containing all tokens.  
- A `.freq` file sorted by frequency (descending) and word (ascending).  
- Summary statistics printed to standard output.  

---

## Directory Structure
```
project/
├─ BST.hpp
├─ BST.cpp
├─ PriorityQueue.hpp
├─ PriorityQueue.cpp
├─ Scanner.hpp
├─ Scanner.cpp
├─ utils.hpp
├─ utils.cpp
├─ main.cpp
├─ Makefile
└─ input_output/
   └─ TheBells.txt
```

---

## Compilation
To build the executable, run:
```bash
make
```
This compiles all source files and produces:
```
./huff_phase2
```

To clean old builds:
```bash
make clean
```

## Running the Program
Place your input file in the `input_output/` directory, then run:
```bash
./huff_phase2 input_output/TheBells.txt
```

**Output files generated:**
- `input_output/TheBells.tokens` — token list from the input  
- `input_output/TheBells.freq` — frequency list sorted by descending count, then ascending word  

**Example output to stdout:**
```
BST height: 12
BST unique words: 49
Total tokens: 83
Min frequency: 1
Max frequency: 11
```


## Implementation Details

### Scanner (reused from Part 1)
- Reads an input file.
- Produces a vector of tokens (lowercased words).
- Writes `.tokens` file.

### BST
- Inserts each token, incrementing existing counts.  
- Provides height, total token count, min/max frequency, and unique word count.  
- Exposes an inorder traversal that returns a vector of `(word, count)` pairs sorted lexicographically.

### PriorityQueue
- Builds from the BST’s `(word, count)` vector.  
- Sorts entries **by descending count, then ascending word** for deterministic results.  
- Writes `.freq` file with one word–count pair per line.


## Example Workflow
```bash
# 1. Build
make

# 2. Run on sample file
./huff_phase2 input_output/TheBells.txt

# 3. View results
cat input_output/TheBells.tokens
cat input_output/TheBells.freq
```
