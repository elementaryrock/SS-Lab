# Banker's Algorithm

## Introduction

The Banker's Algorithm is a deadlock avoidance algorithm developed by Edsger Dijkstra. It is used in operating systems to avoid deadlock by ensuring that the system never enters an unsafe state. The algorithm is named after the banking system where a banker never allocates cash in such a way that he cannot satisfy all customers.

## Key Concepts

### Safe State
A state is considered safe if there exists a sequence of processes such that each process can complete its execution without causing a deadlock.

### Unsafe State
A state where no safe sequence exists, which may lead to deadlock.

### Data Structures Used

1. **Allocation Matrix**: Shows currently allocated resources to each process
2. **Max Need Matrix**: Shows maximum resources each process may need
3. **Need Matrix**: Shows remaining resources each process needs (Max - Allocation)
4. **Available Vector**: Shows currently available resources in the system

## Algorithm Steps

### Step 1: Initialize Data Structures
- Read the number of processes (n) and resource types (m)
- Initialize Allocation, Max Need, and Available matrices
- Calculate Need matrix: Need[i][j] = Max[i][j] - Allocation[i][j]

### Step 2: Safety Algorithm
```
1. Initialize Work = Available and Finish[i] = false for all i
2. Find an index i such that:
   - Finish[i] == false
   - Need[i] <= Work
3. If such i exists:
   - Work = Work + Allocation[i]
   - Finish[i] = true
   - Go to step 2
4. If Finish[i] == true for all i, then system is in safe state
   Otherwise, system is in unsafe state
```

### Step 3: Resource Request Algorithm
When process Pi requests resources Request[i]:

```
1. Check if Request[i] <= Need[i]
   If not, raise error (exceeded maximum claim)

2. Check if Request[i] <= Available
   If not, Pi must wait (resources not available)

3. Temporarily allocate resources:
   - Available = Available - Request[i]
   - Allocation[i] = Allocation[i] + Request[i]
   - Need[i] = Need[i] - Request[i]

4. Run Safety Algorithm:
   - If safe: Grant the request
   - If unsafe: Rollback allocation and deny request
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