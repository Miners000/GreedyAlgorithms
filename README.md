# GreedyAlgorithms
# Cache Eviction Policy Simulator (C++)

Implements and compares three cache eviction policies on the same request sequence:
**FIFO**, **LRU**, and **OPTFF** (Belady's Optimal offline algorithm).

## Authors
Hemanshu Boppana (UFID: 74149423)
Trent Ford (UFID: )

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

## Question 1: Empirical Comparison

Used three nontrivial input files, each with at least 50 requests:

- `data/q1_file1.in` with `k = 3`, `m = 60`
- `data/q1_file2.in` with `k = 4`, `m = 64`
- `data/q1_file3.in` with `k = 5`, `m = 70`

| Input File    | k | m | FIFO | LRU | OPTFF |
| `q1_file1.in` | 3 | 60 | 54 | 56 | 35 |
| `q1_file2.in` | 4 | 64 | 44 | 47 | 29 |
| `q1_file3.in` | 5 | 70 | 45 | 41 | 26 |

### Brief Comments

- OPTFF has the fewest misses in all three files.
- FIFO vs LRU is mixed: FIFO is slightly better in Files 1 and 2, while LRU is better in File 3.
- These results makes sense. OPTFF is an offline optimal benchmark, while FIFO/LRU quality depends on the request pattern.

## Question 2: Bad Sequence for LRU or FIFO

For `k = 3`, a sequence exists where OPTFF has strictly fewer misses than LRU.

- Chosen policy for comparison: `LRU`
- Input file: `data/q2_lru_bad_k3.in`
- Sequence (`m = 12`): `1 2 3 4 1 2 5 1 2 3 4 5`

Computed misses:

| Policy | Misses |
| LRU    | 10 |
| OPTFF  | 7 |

OPTFF is strictly better than LRU on this sequence since it has fewer misses.

Reasoning: OPTFF uses future knowledge to evict the page needed farthest in the future, while LRU only uses past recency and makes locally reasonable but globally suboptimal choices on this pattern.

