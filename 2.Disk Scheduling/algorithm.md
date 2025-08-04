# Disk Scheduling Algorithms

## Introduction

Disk scheduling algorithms are used by operating systems to determine the order in which disk I/O requests should be serviced. The main goal is to minimize the total seek time (time taken by the disk head to move from one track to another) and improve overall system performance.

## Key Concepts

### Seek Time
The time required for the disk head to move from its current position to the desired track.

### Rotational Latency
The time required for the desired sector to rotate under the disk head.

### Transfer Time
The time required to transfer data between the disk and memory.

### Disk Head
The component that reads/writes data on the disk surface by moving across tracks.

## Algorithms Implemented

### 1. FCFS (First Come First Serve)

#### Description
FCFS is the simplest disk scheduling algorithm that services requests in the order they arrive, similar to a queue.

#### Algorithm Steps
```
1. Initialize total_seek_time = 0
2. Set current_position = initial_head_position
3. For each request in the queue:
   a. Calculate seek_distance = |request_position - current_position|
   b. Add seek_distance to total_seek_time
   c. Move head to request_position
   d. Set current_position = request_position
4. Output total_seek_time
```

#### Advantages
- Simple to implement and understand
- Fair - no starvation of requests
- Low overhead

#### Disadvantages
- High seek time due to random head movement
- Poor performance with heavy loads
- No optimization for head movement

### 2. SCAN (Elevator Algorithm)

#### Description
SCAN algorithm moves the disk head in one direction, servicing all requests in that direction, then reverses direction and services requests in the opposite direction.

#### Algorithm Steps
```
1. Divide requests into two groups:
   - Left: requests < current_head_position
   - Right: requests >= current_head_position
2. Add track 0 to left group
3. Sort left group in descending order
4. Sort right group in ascending order
5. Service requests in left group (towards track 0)
6. Service requests in right group (towards end)
7. Calculate total seek distance
```

#### Advantages
- Better performance than FCFS
- Prevents starvation
- Uniform response time

#### Disadvantages
- Requests at the middle tracks get better service
- End tracks may wait longer

### 3. C-SCAN (Circular SCAN)

#### Description
C-SCAN is a variation of SCAN that treats the disk as circular. After reaching one end, the head immediately returns to the other end and continues servicing.

#### Algorithm Steps
```
1. Add current head position, track 0, and last track to request queue
2. Sort all requests in ascending order
3. Find position of current head in sorted array
4. Service requests from current position to end of disk
5. Jump to beginning of disk (track 0)
6. Service remaining requests from beginning to current position
7. Calculate total seek distance including jump
```

#### Advantages
- More uniform response time than SCAN
- Better performance for requests at both ends
- Eliminates bias against certain tracks

#### Disadvantages
- Slightly more complex than SCAN
- May have higher seek time due to circular jump

## Performance Comparison

| Algorithm | Average Seek Time | Fairness | Complexity | Starvation |
|-----------|------------------|----------|------------|------------|
| FCFS      | High             | High     | Low        | None       |
| SCAN      | Medium           | Medium   | Medium     | Possible   |
| C-SCAN    | Low              | High     | Medium     | None       |

## Example Walkthrough

### Given Data
- Request Queue: [98, 183, 37, 122, 14, 124, 65, 67]
- Initial Head Position: 53
- Disk Size: 200 tracks (0-199)

### FCFS Execution
```
Head Movement: 53 → 98 → 183 → 37 → 122 → 14 → 124 → 65 → 67
Seek Distance: 45 + 85 + 146 + 85 + 108 + 110 + 59 + 2 = 640
```

### SCAN Execution (Left First)
```
Left of 53: [37, 14] → sorted: [37, 14, 0]
Right of 53: [98, 183, 122, 124, 65, 67] → sorted: [65, 67, 98, 122, 124, 183]
Head Movement: 53 → 37 → 14 → 0 → 65 → 67 → 98 → 122 → 124 → 183
Seek Distance: 16 + 23 + 14 + 65 + 2 + 31 + 24 + 2 + 59 = 236
```

### C-SCAN Execution
```
Sorted Queue: [0, 14, 37, 53, 65, 67, 98, 122, 124, 183, 199]
Head at position 3 (value 53)
Head Movement: 53 → 65 → 67 → 98 → 122 → 124 → 183 → 199 → 0 → 14 → 37
Seek Distance: 12 + 2 + 31 + 24 + 2 + 59 + 16 + 199 + 14 + 23 = 382
```

## Time Complexity

- **FCFS**: O(n) where n is the number of requests
- **SCAN**: O(n log n) due to sorting
- **C-SCAN**: O(n log n) due to sorting

## Space Complexity

All algorithms: O(n) for storing requests and temporary arrays

## Real-World Applications

1. **Hard Disk Drives**: Traditional mechanical drives benefit most from these algorithms
2. **Operating Systems**: Linux, Windows use variations of these algorithms
3. **Database Systems**: For optimizing disk access patterns
4. **File Systems**: For efficient file allocation and access

## Modern Considerations

- **SSDs**: Solid State Drives don't benefit from these algorithms as they have no mechanical seek time
- **Hybrid Approaches**: Modern systems combine multiple algorithms
- **I/O Schedulers**: Linux uses CFQ, Deadline, and NOOP schedulers
- **Priority Queues**: Some systems implement priority-based scheduling

## Implementation Notes

- The algorithms assume single-head disk systems
- Real systems may have multiple requests arriving simultaneously
- Modern implementations consider request priorities and deadlines
- Some systems use anticipatory scheduling to reduce seek time further