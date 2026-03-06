# GreedyAlgorithms
# Cache Eviction Policy Simulator (C++)

Implements and compares three cache eviction policies on the same request sequence:
**FIFO**, **LRU**, and **OPTFF** (Belady's Optimal offline algorithm).

---

## Repository Structure

```
cache-eviction/
├── src/
│   └── cache_sim.cpp      # Simulator: FIFO, LRU, OPTFF + main()
├── data/
│   ├── example.in         # General mixed-access input
│   └── example.out        # Expected output for example.in
├── tests/
│   └── test_cache.cpp     # 38-test unit + integration suite
├── Makefile
└── README.md
```

---

## Requirements

- C++17-compatible compiler (e.g., `g++ 9+` or `clang++ 9+`)
- `make` (optional but recommended)

---

## Build

```bash
# With make (recommended):
make

# Manually:
g++ -std=c++17 -O2 -o cache_sim src/cache_sim.cpp
```

---

## Run

```bash
./cacheSim <input_file>
```

**Example:**

```bash
./cacheSim data/example.in
```

**Expected output:**

```
FIFO  : 12
LRU   : 14
OPTFF : 8
```

## Input Format

```
k m
r1 r2 r3 ... rm
```

- `k` — cache capacity (integer ≥ 1)
- `m` — number of requests
- `r1 … rm` — integer item IDs (whitespace-separated, may span lines)

---

## Output Format

```
FIFO  : <misses>
LRU   : <misses>
OPTFF : <misses>
```

---

## Assumptions

- All request IDs are non-negative integers fitting in `int`.
- `k ≥ 1`, `m ≥ 0`.
- Input may spread requests over multiple lines; the parser uses `>>` which
  splits on all whitespace.
- Ties in OPTFF (multiple items with `next_use = INT_MAX`) are broken by
  whichever `unordered_map` iteration hits first; any tie-breaking is valid
  since all such items are equally optimal to evict.

---

---

# Written Component

## Algorithm Descriptions

### FIFO (First-In, First-Out)

