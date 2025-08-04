# Viva Questions - Disk Scheduling Algorithms
## CSL 331 System Software Lab - KTU S5

---

## Basic Concepts

### Q1: What is disk scheduling?
**Answer:** Disk scheduling is the process of deciding the order in which disk I/O requests should be serviced by the operating system. The main goal is to minimize the total seek time and improve overall system performance by reducing the movement of the disk head.

### Q2: What are the main components of disk access time?
**Answer:**
- **Seek Time:** Time to move the disk head to the correct track
- **Rotational Latency:** Time for the desired sector to rotate under the head
- **Transfer Time:** Time to actually read/write the data
- **Controller Overhead:** Time for command processing

### Q3: Why is seek time the most significant component in disk access time?
**Answer:** Seek time is typically the largest component because it involves physical movement of the disk head across tracks. While rotational latency and transfer time are relatively small and constant, seek time varies greatly depending on the distance the head needs to travel.

### Q4: What is the difference between track, sector, and cylinder?
**Answer:**
- **Track:** Concentric circles on a disk surface where data is stored
- **Sector:** Smallest addressable unit on a track (like a slice of pie)
- **Cylinder:** Set of tracks at the same distance from center across all disk surfaces

### Q5: What is meant by disk head movement?
**Answer:** Disk head movement refers to the physical motion of the read/write head from one track to another. This movement is mechanical and takes time, which is why minimizing unnecessary head movements is crucial for performance.

---

## FCFS Algorithm

### Q6: Explain the FCFS disk scheduling algorithm.
**Answer:** FCFS (First Come First Serve) services disk requests in the order they arrive, similar to a queue. It's the simplest algorithm where requests are processed sequentially without any optimization for head movement.

### Q7: What are the advantages of FCFS?
**Answer:**
1. Simple to implement and understand
2. Fair - no request starvation
3. Low computational overhead
4. Predictable response time for each request

### Q8: What are the disadvantages of FCFS?
**Answer:**
1. High seek time due to random head movement
2. Poor performance with heavy I/O loads
3. No optimization - may cause excessive head thrashing
4. Inefficient use of disk bandwidth

### Q9: In what scenarios would FCFS be preferred?
**Answer:** FCFS might be preferred in:
1. Systems with very light I/O loads
2. Real-time systems where fairness is more important than efficiency
3. Simple embedded systems where implementation complexity must be minimal
4. Systems where request patterns are already optimized

### Q10: How do you calculate total seek time in FCFS?
**Answer:** Total seek time = Σ|current_position - next_request_position| for all requests, where the head moves from current position to each request position in sequence.

---

## SCAN Algorithm

### Q11: Explain the SCAN (Elevator) algorithm.
**Answer:** SCAN algorithm moves the disk head in one direction, servicing all requests in that direction until it reaches the end, then reverses direction and services requests in the opposite direction. It's called the elevator algorithm because it works like an elevator serving floors.

### Q12: How does SCAN decide the initial direction?
**Answer:** In our implementation, SCAN goes towards track 0 first (downward direction), then moves upward. However, the direction can be predetermined based on system policy or the distribution of requests.

### Q13: What are the advantages of SCAN?
**Answer:**
1. Better performance than FCFS
2. Prevents starvation of requests
3. More uniform response time
4. Reduces wild head movements
5. Good throughput under heavy loads

### Q14: What are the disadvantages of SCAN?
**Answer:**
1. Requests at the middle tracks get better service than those at the ends
2. End tracks may experience longer waiting times
3. More complex than FCFS
4. May not be optimal for all request patterns

### Q15: Why is SCAN called the elevator algorithm?
**Answer:** SCAN is called the elevator algorithm because it works exactly like an elevator in a building - it moves in one direction, stops at all requested floors in that direction, then changes direction and serves requests in the opposite direction.

---

## C-SCAN Algorithm

### Q16: Explain the C-SCAN (Circular SCAN) algorithm.
**Answer:** C-SCAN treats the disk as circular. After reaching one end of the disk, the head immediately returns to the other end and continues servicing requests in the same direction, providing more uniform response time.

### Q17: How is C-SCAN different from SCAN?
**Answer:**
- **SCAN:** Reverses direction at each end, creating a back-and-forth motion
- **C-SCAN:** Always moves in one direction, jumping back to the beginning after reaching the end
- **C-SCAN:** Provides more uniform response time for all tracks

### Q18: What are the advantages of C-SCAN?
**Answer:**
1. More uniform response time than SCAN
2. Better performance for requests at both ends of the disk
3. Eliminates bias against certain track locations
4. Predictable access patterns

### Q19: What are the disadvantages of C-SCAN?
**Answer:**
1. Slightly more complex than SCAN
2. May have higher total seek time due to the return jump
3. The return sweep doesn't service any requests (wasted movement)
4. Not always optimal for all workloads

### Q20: Why does C-SCAN add track 0 and the last track to the request queue?
**Answer:** Adding track 0 and the last track ensures that the algorithm properly handles the circular nature by defining the boundaries. This helps in calculating the correct seek distance when the head jumps from the last track back to track 0.

---

## Implementation Details

### Q21: Explain the sorting logic used in SCAN algorithm.
**Answer:** 
- **Left array:** Contains requests below current head position, sorted in descending order (to visit them while going down)
- **Right array:** Contains requests above current head position, sorted in ascending order (to visit them while going up)
- Track 0 is added to the left array to ensure the head goes to the beginning

### Q22: How does the bubble sort work in the code?
**Answer:** Bubble sort compares adjacent elements and swaps them if they're in wrong order. It repeats this process until no more swaps are needed. In our code, it's used to sort request arrays in ascending or descending order as needed.

### Q23: What is the purpose of the `abs()` function?
**Answer:** The `abs()` function returns the absolute value, ensuring that the distance calculation is always positive regardless of whether the head moves up or down the tracks.

### Q24: Why do we use separate arrays for left and right in SCAN?
**Answer:** Separate arrays allow us to sort requests below and above the current head position differently - left array in descending order (for downward movement) and right array in ascending order (for upward movement).

### Q25: Explain the role of the `pos` variable in C-SCAN.
**Answer:** The `pos` variable stores the index of the current head position in the sorted request array. This helps determine where to start servicing requests and where to split the circular traversal.

---

## Performance Analysis

### Q26: Which algorithm generally provides the best performance?
**Answer:** Performance depends on the request pattern, but generally:
- **SCAN** often provides the best balance of performance and fairness
- **C-SCAN** provides the most uniform response time
- **FCFS** has the worst performance but is fairest

### Q27: How do you calculate the efficiency of a disk scheduling algorithm?
**Answer:** Efficiency can be measured by:
1. **Total seek time:** Lower is better
2. **Average response time:** Time from request arrival to completion
3. **Throughput:** Number of requests served per unit time
4. **Variance in response time:** Lower variance means more predictable performance

### Q28: In what scenarios would SCAN perform poorly?
**Answer:** SCAN performs poorly when:
1. Most requests are concentrated at one end of the disk
2. Requests arrive in patterns that conflict with the scanning direction
3. Real-time systems where predictable response time is crucial
4. Very light loads where the overhead of sorting isn't justified

### Q29: Why might C-SCAN have higher total seek time than SCAN?
**Answer:** C-SCAN may have higher total seek time because of the "return jump" from the last track back to track 0. This jump covers the entire disk width but doesn't service any requests, adding to the total seek distance.

### Q30: How does request arrival pattern affect algorithm performance?
**Answer:** 
- **Random patterns:** SCAN and C-SCAN perform much better than FCFS
- **Sequential patterns:** All algorithms perform similarly well
- **Clustered patterns:** Performance depends on cluster location relative to current head position

---

## Real-World Applications

### Q31: Are these algorithms still relevant with modern SSDs?
**Answer:** These algorithms are less relevant for SSDs because:
1. SSDs have no mechanical seek time
2. Access time is uniform across all locations
3. However, they're still important for traditional HDDs
4. The concepts are useful for understanding I/O optimization

### Q32: How do modern operating systems implement disk scheduling?
**Answer:** Modern OS use sophisticated schedulers like:
- **Linux:** CFQ (Completely Fair Queuing), Deadline, NOOP
- **Windows:** Uses anticipatory scheduling and request merging
- **Hybrid approaches:** Combine multiple algorithms based on workload

### Q33: What is the role of disk scheduling in database systems?
**Answer:** Database systems use disk scheduling to:
1. Optimize query performance by ordering disk reads
2. Minimize transaction response time
3. Improve concurrent access patterns
4. Reduce disk head thrashing during heavy operations

### Q34: How does disk scheduling relate to file system performance?
**Answer:** File systems benefit from disk scheduling by:
1. Optimizing file allocation strategies
2. Reducing fragmentation impact
3. Improving directory traversal performance
4. Enhancing overall system responsiveness

### Q35: What is anticipatory scheduling?
**Answer:** Anticipatory scheduling delays servicing a request for a short time, anticipating that a nearby request might arrive soon. This can reduce total seek time by batching nearby requests together.

---

## Advanced Concepts

### Q36: What is the difference between online and offline disk scheduling?
**Answer:**
- **Online:** Decisions made as requests arrive (like our algorithms)
- **Offline:** All requests known in advance, optimal solution possible
- **Real systems:** Use online algorithms as requests arrive dynamically

### Q37: How do you handle priority requests in disk scheduling?
**Answer:** Priority can be handled by:
1. Separate queues for different priorities
2. Weighted algorithms that favor high-priority requests
3. Deadline-based scheduling for time-critical requests
4. Hybrid approaches combining priority with position optimization

### Q38: What is disk arm scheduling vs. disk scheduling?
**Answer:**
- **Disk scheduling:** Decides order of requests
- **Disk arm scheduling:** Specifically refers to optimizing the mechanical arm movement
- **Modern context:** Terms often used interchangeably

### Q39: How does rotational latency optimization work?
**Answer:** Some advanced algorithms consider rotational position:
1. SPTF (Shortest Positioning Time First)
2. Consider both seek time and rotational delay
3. More complex but can provide better performance
4. Requires detailed knowledge of disk geometry

### Q40: What are the trade-offs between fairness and performance in disk scheduling?
**Answer:**
- **FCFS:** Maximum fairness, poor performance
- **SCAN/C-SCAN:** Good balance of both
- **Shortest Seek Time First:** Best performance, poor fairness
- **Real systems:** Often use hybrid approaches to balance both concerns

---

## Code-Specific Questions

### Q41: Why do we add track 0 to the left array in SCAN?
**Answer:** Adding track 0 ensures that the disk head travels to the beginning of the disk during the downward sweep, which is essential for the SCAN algorithm's complete traversal pattern.

### Q42: What happens if all requests are on one side of the current head position?
**Answer:** 
- **SCAN:** Will still go to the boundary (track 0 or end), then return to service requests
- **C-SCAN:** Will complete the circular sweep even if no requests are on the other side
- **FCFS:** Will service requests in order regardless of position

### Q43: How does the menu system enhance the program's educational value?
**Answer:** The menu system allows:
1. Interactive comparison of different algorithms
2. Testing with the same input data
3. Understanding performance differences
4. Educational exploration of algorithm behavior

### Q44: What would happen if we don't sort the arrays in SCAN?
**Answer:** Without sorting:
1. The algorithm wouldn't work correctly
2. Head movement wouldn't be optimized
3. Performance would be similar to or worse than FCFS
4. The fundamental principle of directional movement would be violated

### Q45: Why is the disk size parameter important for C-SCAN?
**Answer:** Disk size is crucial for C-SCAN because:
1. It defines the boundary for the circular jump
2. Helps calculate the return distance from last track to track 0
3. Ensures proper implementation of the circular nature
4. Affects the total seek time calculation

---

*Note: These questions comprehensively cover disk scheduling algorithms from basic concepts to advanced implementation details. Students should understand both the theoretical aspects and practical implementation as demonstrated in the provided C program.*