#include <stdio.h>
#include <stdlib.h>

double awt=0,atat=0;

struct Process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int pr;
};

void fcfs(struct Process proc[], int n)
{
    awt=0;
    atat=0;
    for (int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
            {
                if(proc[j].at>proc[j].at || proc[j].at==proc[j].at && proc[j].pid>proc[j].pid)
                {
                    struct Process temp = proc[i];
                    proc[i] = proc[i+1];
                    proc[i+1] = temp;
                }
            }
    }
    proc[0].ct = proc[0].at + proc[0].bt;
    proc[0].tat = proc[0].ct - proc[0].at;
    proc[0].wt = proc[0].tat - proc[0].bt;
    for(int i=1;i<n;i++)
    {
        if (proc[i].at > proc[i-1].ct)
        {
            proc[i].ct = proc[i].at + proc[i].bt;
        }
        else
        {
            proc[i].ct = proc[i-1].ct + proc[i].bt;
        }
        proc[i].tat = proc[i].ct - proc[i].at;
        proc[i].wt = proc[i].tat - proc[i].bt;
    }
    printf("\nPid\tAt\tBt\tCt\tTat\tWt\n");
    for (int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",proc[i].pid,proc[i].at,proc[i].bt,proc[i].ct,proc[i].tat,proc[i].wt);
        printf("\n");
        awt += proc[i].wt;
        atat += proc[i].tat;
    }
    awt /= n;
    atat /= n;
    printf("Average Waiting Time: %f\nAverage Turnaround Time: %f\n", awt, atat);
}

void sjf(struct Process proc[], int n)
{
    awt=0;
    atat=0;
    for (int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(proc[j].at>proc[j+1].at || proc[j].at==proc[j+1].at && proc[j].pid>proc[j+1].pid)
            {
                struct Process temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }

    int time = 0,completed = 0;
    while (completed < n)
    {
        int count = 0;
        for (int i=completed;i<n;i++)
            {
                if (proc[i].at<=time)
                    {
                        count++;
                    }
            }
        if (count==0)
            {
                time = proc[completed].at;
                continue;
            }
        if (count>1)
            {
                for(int i=completed;i<completed+count;i++)
                    {
                        for(int j=completed;j<completed+count-1;j++)
                            {
                                if(proc[j].bt>proc[j+1].bt || proc[j].bt==proc[j+1].bt && proc[j].pid>proc[j+1].pid)
                                    {
                                        struct Process temp = proc[j];
                                        proc[j] = proc[j+1];
                                        proc[j+1] = temp;
                                    }

                            }
                    }
            }
        if(proc[completed].at>time)
            {
                time = proc[completed].at;
            }
        time = time + proc[completed].bt;
        proc[completed].ct = time;
        proc[completed].tat = proc[completed].ct - proc[completed].at;
        proc[completed].wt = proc[completed].tat - proc[completed].bt;
        completed++;
    }
    for (int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(proc[j].pid>proc[j+1].pid)
            {
                struct Process temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
    printf("\nPid\tAt\tBt\tCt\tTat\tWt\n");
    for (int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",proc[i].pid,proc[i].at,proc[i].bt,proc[i].ct,proc[i].tat,proc[i].wt);
        printf("\n");
        awt += proc[i].wt;
        atat += proc[i].tat;
    }
    awt /= n;
    atat /= n;
    printf("Average Waiting Time: %f\nAverage Turnaround Time: %f\n", awt, atat);
}

void priority(struct Process proc[], int n)
{
    awt=0;
    atat=0;
    printf("\nEnter the priority of each process:\n");
    for (int i=0;i<n;i++)
        {
            scanf("%d", &proc[i].pr);
        }
    for (int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(proc[j].at>proc[j+1].at || proc[j].at==proc[j+1].at && proc[j].pid>proc[j+1].pid)
            {
                struct Process temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }

    int time = 0,completed = 0;
    while (completed < n)
    {
        int count = 0;
        for (int i=completed;i<n;i++)
            {
                if (proc[i].at<=time)
                    {
                        count++;
                    }
            }
        if (count==0)
            {
                time = proc[completed].at;
                continue;
            }
        if (count>1)
            {
                for(int i=completed;i<completed+count;i++)
                    {
                        for(int j=completed;j<completed+count-1;j++)
                            {
                                if(proc[j].pr>proc[j+1].pr)
                                    {
                                        struct Process temp = proc[j];
                                        proc[j] = proc[j+1];
                                        proc[j+1] = temp;
                                    }

                            }
                    }
            }
        if(proc[completed].at>time)
            {
                time = proc[completed].at;
            }
        time = time + proc[completed].bt;
        proc[completed].ct = time;
        proc[completed].tat = proc[completed].ct - proc[completed].at;
        proc[completed].wt = proc[completed].tat - proc[completed].bt;
        completed++;
    }
    for (int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(proc[j].pid>proc[j+1].pid)
            {
                struct Process temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
    printf("\nPid\tAt\tBt\tCt\tTat\tWt\tPr\n");
    for (int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",proc[i].pid,proc[i].at,proc[i].bt,proc[i].ct,proc[i].tat,proc[i].wt,proc[i].pr);
        printf("\n");
        awt += proc[i].wt;
        atat += proc[i].tat;
    }
    awt /= n;
    atat /= n;
    printf("Average Waiting Time: %f\nAverage Turnaround Time: %f\n", awt, atat);
}

void roundrobin(struct Process proc[], int n)
{
    awt = 0;
    atat = 0;
    int quantum;
    printf("\nEnter time quantum: ");
    scanf("%d", &quantum);
    
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(proc[j].at > proc[j+1].at || (proc[j].at == proc[j+1].at && proc[j].pid > proc[j+1].pid))
            {
                struct Process temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
    
    int rbt[n];
    for (int i = 0; i < n; i++)
    {
        rbt[i] = proc[i].bt;
    }
    
    int time = 0;
    int completed = 0;
    int queue[1000]; 
    int front = 0, rear = -1;
    int inQueue[n]; 
    
    for(int i = 0; i < n; i++)
    {
        inQueue[i] = 0;
    }
    
    if(proc[0].at <= time)
    {
        queue[++rear] = 0;
        inQueue[0] = 1;
    }
    
    while(completed < n)
    {
        if(front > rear)
        {
            for(int i = 0; i < n; i++)
            {
                if(rbt[i] > 0 && proc[i].at > time)
                {
                    time = proc[i].at;
                    queue[++rear] = i;
                    inQueue[i] = 1;
                    break;
                }
            }
        }
        
        if(front <= rear)
        {
            int current = queue[front++];
            
            int execTime = (rbt[current] < quantum) ? rbt[current] : quantum;
            time += execTime;
            rbt[current] -= execTime;
            
            for(int i = 0; i < n; i++)
            {
                if(rbt[i] > 0 && inQueue[i] == 0 && proc[i].at <= time)
                {
                    queue[++rear] = i;
                    inQueue[i] = 1;
                }
            }
            
            if(rbt[current] == 0)
            {
                proc[current].ct = time;
                proc[current].tat = proc[current].ct - proc[current].at;
                proc[current].wt = proc[current].tat - proc[current].bt;
                completed++;
                inQueue[current] = 0;
            }
            else
            {
                queue[++rear] = current;
            }
        }
    }
    
    for (int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - 1 - i; j++)
        {
            if(proc[j].pid > proc[j+1].pid)
            {
                struct Process temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
    
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].ct, proc[i].tat, proc[i].wt);
        awt += proc[i].wt;
        atat += proc[i].tat;
    }
    
    awt /= n;
    atat /= n;
    printf("\nAverage Waiting Time: %.2f\n", awt);
    printf("Average Turnaround Time: %.2f\n", atat);
}

void main()
{
    double atat,awt;
    int num_processes,choice;
    char continue_loop;
    printf("\nEnter the number of processes: ");
    scanf("%d", &num_processes);
    struct Process processes[num_processes];
    for (int i=0;i<num_processes;i++)
        {
            printf("Enter pid,at,bt");
            scanf("%d%d%d",&processes[i].pid,&processes[i].at,&processes[i].bt);
        }
    do
    {
        printf("\nMenu\n1.Fcfs\n2.Sjf\n3.Priority\n4.Round Robin\n5.EXIT");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
            printf("Fcfs");
            fcfs(processes,num_processes);
            break;

            case 2:
            printf("Sjf");
            sjf(processes,num_processes);
            break;

            case 3:
            printf("Priority");
            priority(processes,num_processes);
            break;

            case 4:
            printf("Round Robin");
            roundrobin(processes,num_processes);
            break;

            case 5:
            printf("EXIT");
            exit(0);
            break;

        }
        if (choice!=0)
        {
            printf("Do you want to continue? (y/n): ");
            scanf(" %c", &continue_loop);
        }
        else
        {
            continue_loop = 'n';
        }
    }
    while (continue_loop == 'y');
}
