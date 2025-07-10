# PROGRAM - 1
## CPU SCHEDULING

### AIM
To implement a menu driven program for CPU scheduling: FCFS, SJF, Priority and Round Robin in C.

### ALGORITHM

1. Initialize required variables for the program.
2. Define a structure named process in which the variables for second, third is initialized.
3. Display the MENU: 1.FCFS 2.SJF 3.Priority 4.Round Robin and 5.EXIT.
4. Read and enter the choice.
5. Switch choice, if choice 1: FCFS
6. Enter and read the no. of processes.
7. Using a for loop enter and read PID, AT, BT of each process.
8. For i = 0 to n-1 repeat,
   For j = 0 to n-1-i repeat,
   If at[j] > at[j+1] and OR at[j] = at[j+1] 
   AND pid[j] > pid[j+1] then,
   Swap at[j], bt[j] and pid[j].
9. Set ct[0] = at[0] + bt[0],
   Set tat[0] = ct[0] - at[0],
   Set wt[0] = tat[0] - bt[0].
10. For i = 1 to n repeat,
    Set ct[i] = ct[i-1] + bt[i],
    Set tat[i] = ct[i] - at[i],
    Set wt[i] = tat[i] - bt[i].
11. Calculate average waiting time and average turnaround time.
12. Display the process table with PID, AT, BT, CT, TAT, WT.
13. Display average waiting time and average turnaround time.
14. If choice 2: SJF
15. Read the number of processes.
16. Read PID, AT, BT for each process.
17. Sort processes by arrival time.
18. Initialize time = 0, completed = 0.
19. While completed < n repeat,
    19.1 Find all processes arrived by current time.
    19.2 If no process arrived then advance time.
    19.3 Among arrived processes, select shortest burst time.
    19.4 Execute selected process completely.
    19.5 Update completion time and mark as completed.
    19.6 Increment completed count.
20. Calculate TAT and WT for each process.
21. Calculate and display averages.
22. If choice 3: Priority
23. Read number of processes and priority for each.
24. Sort processes by arrival time.
25. Initialize time = 0, completed = 0.
26. While completed < n repeat,
    26.1 Find all processes arrived by current time.
    26.2 Among arrived processes, select highest priority.
    26.3 Execute selected process completely.
    26.4 Update completion time and mark as completed.
27. Calculate TAT, WT and display results.
28. If choice 4: Round Robin
29. Read number of processes and time quantum.
30. Read process details and sort by arrival time.
31. Initialize ready queue and remaining burst time array.
32. Initialize time = 0, completed = 0.
33. Add first arrived process to ready queue.
34. While completed < n repeat,
    34.1 If queue empty, advance time to next arrival.
    34.2 Remove process from front of queue.
    34.3 Execute for min(quantum, remaining_time).
    34.4 Update time and remaining time.
    34.5 Check for newly arrived processes and add to queue.
    34.6 If process completed, calculate CT, TAT, WT.
    34.7 Else add process back to end of queue.
35. Calculate and display averages.
36. If choice 5: EXIT, terminate program.
37. Ask user to continue (y/n).
38. Repeat from step 3 if user wants to continue.
39. STOP.

**Time Complexity:** O(N²)
**Space Complexity:** O(N)

- Read process_id[i], arrival_time[i], burst_time[i]

**Step 4:** Sort processes based on arrival_time in ascending order

- FOR i = 0 to n-2 DO
  - FOR j = 0 to n-2-i DO
    - IF arrival_time[j] > arrival_time[j+1] THEN
      - Swap process[j] and process[j+1]

**Step 5:** Calculate completion time for each process

- completion_time[0] = arrival_time[0] + burst_time[0]
- FOR i = 1 to n-1 DO
  - IF arrival_time[i] > completion_time[i-1] THEN
    - completion_time[i] = arrival_time[i] + burst_time[i]
  - ELSE
    - completion_time[i] = completion_time[i-1] + burst_time[i]

**Step 6:** Calculate turnaround time and waiting time

- FOR i = 0 to n-1 DO
  - turnaround_time[i] = completion_time[i] - arrival_time[i]
  - waiting_time[i] = turnaround_time[i] - burst_time[i]

**Step 7:** Calculate average waiting time and average turnaround time

- avg_waiting_time = (sum of all waiting_time) / n
- avg_turnaround_time = (sum of all turnaround_time) / n

**Step 8:** Display the results in tabular format

**Step 9:** STOP

---

## **Algorithm 2: Shortest Job First (SJF) Scheduling**

### **AIM:**

To implement Shortest Job First CPU scheduling algorithm.

### **ALGORITHM:**

**Step 1:** START

**Step 2:** Read the number of processes n

**Step 3:** FOR i = 0 to n-1 DO

- Read process_id[i], arrival_time[i], burst_time[i]

**Step 4:** Sort processes based on arrival_time in ascending order

**Step 5:** Initialize current_time = 0, completed = 0

**Step 6:** WHILE completed < n DO

- **Step 6.1:** Find all processes that have arrived by current_time
- **Step 6.2:** IF no process has arrived THEN
  - current_time = earliest arrival_time among remaining processes
- **Step 6.3:** Among arrived processes, select process with minimum burst_time
- **Step 6.4:** IF multiple processes have same burst_time THEN
  - Select process with smaller process_id
- **Step 6.5:** Execute selected process completely
  - current_time = current_time + burst_time[selected_process]
  - completion_time[selected_process] = current_time
- **Step 6.6:** Mark selected process as completed
- **Step 6.7:** completed = completed + 1

**Step 7:** Calculate turnaround time and waiting time for each process

- FOR i = 0 to n-1 DO
  - turnaround_time[i] = completion_time[i] - arrival_time[i]
  - waiting_time[i] = turnaround_time[i] - burst_time[i]

**Step 8:** Calculate averages and display results

**Step 9:** STOP

---

## **Algorithm 3: Priority Scheduling**

### **AIM:**

To implement Priority based CPU scheduling algorithm.

### **ALGORITHM:**

**Step 1:** START

**Step 2:** Read the number of processes n

**Step 3:** FOR i = 0 to n-1 DO

- Read process_id[i], arrival_time[i], burst_time[i], priority[i]

**Step 4:** Sort processes based on arrival_time in ascending order

**Step 5:** Initialize current_time = 0, completed = 0

**Step 6:** WHILE completed < n DO

- **Step 6.1:** Find all processes that have arrived by current_time
- **Step 6.2:** IF no process has arrived THEN
  - current_time = earliest arrival_time among remaining processes
- **Step 6.3:** Among arrived processes, select process with highest priority (lowest priority number)
- **Step 6.4:** IF multiple processes have same priority THEN
  - Select process that arrived first (FCFS)
- **Step 6.5:** Execute selected process completely
  - current_time = current_time + burst_time[selected_process]
  - completion_time[selected_process] = current_time
- **Step 6.6:** Mark selected process as completed
- **Step 6.7:** completed = completed + 1

**Step 7:** Calculate turnaround time and waiting time for each process

**Step 8:** Calculate averages and display results

**Step 9:** STOP

---

## **Algorithm 4: Round Robin Scheduling**

### **AIM:**

To implement Round Robin CPU scheduling algorithm.

### **ALGORITHM:**

**Step 1:** START

**Step 2:** Read the number of processes n

**Step 3:** Read time_quantum

**Step 4:** FOR i = 0 to n-1 DO

- Read process_id[i], arrival_time[i], burst_time[i]
- remaining_time[i] = burst_time[i]

**Step 5:** Sort processes based on arrival_time in ascending order

**Step 6:** Initialize ready_queue, current_time = 0, completed = 0

**Step 7:** Add first arrived process to ready_queue

**Step 8:** WHILE completed < n DO

- **Step 8.1:** IF ready_queue is empty THEN
  - Find next process that will arrive
  - current_time = arrival_time of next process
  - Add that process to ready_queue
- **Step 8.2:** Remove front process from ready_queue
- **Step 8.3:** Calculate execution_time = min(time_quantum, remaining_time[current_process])
- **Step 8.4:** current_time = current_time + execution_time
- **Step 8.5:** remaining_time[current_process] = remaining_time[current_process] - execution_time
- **Step 8.6:** Check for newly arrived processes and add them to ready_queue
- **Step 8.7:** IF remaining_time[current_process] = 0 THEN
  - completion_time[current_process] = current_time
  - completed = completed + 1
- **Step 8.8:** ELSE
  - Add current_process back to end of ready_queue

**Step 9:** Calculate turnaround time and waiting time for each process

**Step 10:** Calculate averages and display results

**Step 11:** STOP

---

## **FORMULAS USED:**

1. **Completion Time (CT):** Time at which process completes execution
2. **Turnaround Time (TAT):** CT - AT
3. **Waiting Time (WT):** TAT - BT
4. **Average Waiting Time:** Σ(WT) / n
5. **Average Turnaround Time:** Σ(TAT) / n

Where:

- AT = Arrival Time
- BT = Burst Time
- n = Number of processes

---

## **OVERALL PROGRAM ALGORITHM**

### **AIM:**

To implement a complete CPU scheduling simulator with multiple scheduling algorithms.

### **DATA STRUCTURE:**

```c
struct Process {
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
    int pr;         // Priority (for priority scheduling)
};
```

### **MAIN ALGORITHM:**

**Step 1:** START

**Step 2:** Initialize global variables

- awt = 0 (average waiting time)
- atat = 0 (average turnaround time)

**Step 3:** READ number_of_processes

**Step 4:** Declare array of Process structures

- Process processes[number_of_processes]

**Step 5:** Input process details

- FOR i = 0 to number_of_processes-1 DO
  - READ processes[i].pid, processes[i].at, processes[i].bt

**Step 6:** Display menu and process user choice

- DO
  - **Step 6.1:** Display menu options:
    - 1.  FCFS
    - 2.  SJF
    - 3.  Priority
    - 4.  Round Robin
    - 5.  EXIT
  - **Step 6.2:** READ user_choice
  - **Step 6.3:** SWITCH user_choice
    - CASE 1: CALL fcfs(processes, number_of_processes)
    - CASE 2: CALL sjf(processes, number_of_processes)
    - CASE 3: CALL priority(processes, number_of_processes)
    - CASE 4: CALL roundrobin(processes, number_of_processes)
    - CASE 5: EXIT program
  - **Step 6.4:** IF user_choice != 5 THEN
    - READ continue_choice (y/n)
- WHILE continue_choice == 'y'

**Step 7:** STOP

### **FUNCTION PROTOTYPES:**

1. **fcfs(struct Process proc[], int n)**

   - Implements First Come First Serve scheduling
   - Non-preemptive algorithm
   - Sorts by arrival time, processes in order

2. **sjf(struct Process proc[], int n)**

   - Implements Shortest Job First scheduling
   - Non-preemptive algorithm
   - Selects process with minimum burst time among arrived processes

3. **priority(struct Process proc[], int n)**

   - Implements Priority based scheduling
   - Non-preemptive algorithm
   - Selects process with highest priority among arrived processes
   - Takes priority input from user

4. **roundrobin(struct Process proc[], int n)**
   - Implements Round Robin scheduling
   - Preemptive algorithm with time quantum
   - Uses circular queue for process management
   - Takes time quantum input from user

### **COMMON OPERATIONS IN ALL FUNCTIONS:**

**Step A:** Sort processes by arrival time
**Step B:** Initialize timing variables
**Step C:** Execute scheduling logic (specific to each algorithm)
**Step D:** Calculate completion time, turnaround time, waiting time
**Step E:** Calculate average waiting time and turnaround time
**Step F:** Display results in tabular format
**Step G:** Sort by process ID for final display

### **MEMORY ORGANIZATION:**

```
Global Variables:
├── awt (double) - Average Waiting Time
└── atat (double) - Average Turnaround Time

Process Structure Array:
├── pid[n] - Process IDs
├── at[n] - Arrival Times
├── bt[n] - Burst Times
├── ct[n] - Completion Times
├── tat[n] - Turnaround Times
├── wt[n] - Waiting Times
└── pr[n] - Priorities (when needed)

Algorithm Specific Variables:
├── time_quantum (Round Robin)
├── ready_queue[] (Round Robin)
├── remaining_time[] (Round Robin)
└── priority[] (Priority Scheduling)
```

### **PROGRAM FLOW:**

```
START
  ↓
INPUT: Number of processes and their details
  ↓
DISPLAY: Menu with scheduling options
  ↓
USER SELECTION: Choose algorithm
  ↓
EXECUTE: Selected scheduling algorithm
  ↓
CALCULATE: Performance metrics
  ↓
DISPLAY: Results in tabular format
  ↓
CONTINUE?: Ask user to continue or exit
  ↓
END (if exit) or REPEAT (if continue)
```

---
