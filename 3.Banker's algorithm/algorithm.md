# Banker's Algorithm

## Introduction

The Banker's Algorithm is a deadlock avoidance algorithm developed by Edsger Dijkstra. It is used in operating systems to avoid deadlock by ensuring that the system never enters an unsafe state. The algorithm is named after the banking system where a banker never allocates cash in such a way that he cannot satisfy all customers.

## Key Concepts

### Safe State
A state is considered safe if there exists a sequence of processes such that each process can complete its execution without causing a deadlock.

### Unsafe State
A state where no safe sequence exists, which may lead to deadlock.

### Data Structures Used

1. **Allocation Matrix (alloc)**: Shows currently allocated resources to each process
2. **Max Need Matrix (max)**: Shows maximum resources each process may need
3. **Need Matrix (need)**: Shows remaining resources each process needs (Max - Allocation)
4. **Available Vector (avl)**: Shows currently available resources in the system
5. **Total Resources (T)**: Total instances of each resource type

## Algorithm Steps

### Step 1: Input and Initialize
- Read number of processes (n) and resource types (m)
- Read total instances of each resource type (T[])
- Read Allocation matrix (alloc[][])
- Read Max Need matrix (max[][])

### Step 2: Calculate Available Resources
```
For each resource type j:
    c = sum of all allocated instances of resource j
    avl[j] = T[j] - c
```

### Step 3: Calculate Need Matrix
```
For each process i and resource j:
    need[i][j] = max[i][j] - alloc[i][j]
```

### Step 4: Safety Algorithm
```
1. Initialize:
   - work[] = avl[] (copy available resources)
   - finish[i] = 0 for all processes (none finished)
   - safeseq[] = empty sequence

2. Repeat n times:
   For each process i:
     If finish[i] == 0:
       flag = 0
       For each resource j:
         If need[i][j] > work[j]:
           flag = 1
           break
       If flag == 0:
         safeseq[d++] = i
         work[j] += alloc[i][j] for all j
         finish[i] = 1

3. Count finished processes:
   If all processes finished: System is SAFE
   Otherwise: System is UNSAFE
```

## Example Walkthrough

Consider a system with:
- 5 processes (P0, P1, P2, P3, P4)
- 3 resource types (A, B, C)

### Initial State:
```
Allocation Matrix:
Process  A  B  C
P0       0  1  0
P1       2  0  0
P2       3  0  2
P3       2  1  1
P4       0  0  2

Max Need Matrix:
Process  A  B  C
P0       7  5  3
P1       3  2  2
P2       9  0  2
P3       2  2  2
P4       4  3  3

Available: A=3, B=3, C=2
```

### Need Matrix Calculation:
```
Need Matrix:
Process  A  B  C
P0       7  4  3
P1       1  2  2
P2       6  0  0
P3       0  1  1
P4       4  3  1
```

### Safety Check:
1. Work = [3, 3, 2], Finish = [F, F, F, F, F]
2. Check P1: Need[1] = [1,2,2] <= Work[3,3,2] ✓
   - Work = [3,3,2] + [2,0,0] = [5,3,2]
   - Finish[1] = True
3. Check P3: Need[3] = [0,1,1] <= Work[5,3,2] ✓
   - Work = [5,3,2] + [2,1,1] = [7,4,3]
   - Finish[3] = True
4. Continue until all processes finish...

Safe sequence: P1 → P3 → P4 → P2 → P0

## Advantages

1. **Deadlock Prevention**: Guarantees that deadlock will never occur
2. **Resource Utilization**: Allows maximum possible resource utilization while maintaining safety
3. **Dynamic**: Can handle dynamic resource requests

## Disadvantages

1. **Overhead**: Requires advance knowledge of maximum resource requirements
2. **Conservative**: May deny requests that wouldn't actually cause deadlock
3. **Scalability**: Performance degrades with large numbers of processes and resources

## Time Complexity

- Safety Algorithm: O(n²m) where n = processes, m = resource types
- Resource Request: O(n²m) including safety check

## Applications

1. **Operating Systems**: Process scheduling and resource allocation
2. **Database Systems**: Transaction management and lock allocation
3. **Distributed Systems**: Resource management in distributed environments

## Implementation Notes

- The algorithm assumes that processes will eventually release all allocated resources
- Maximum resource requirements must be known in advance
- The algorithm is more theoretical than practical due to its conservative nature
- Modern systems often use other deadlock handling strategies like detection and recovery