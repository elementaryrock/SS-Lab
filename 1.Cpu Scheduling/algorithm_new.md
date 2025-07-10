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
