#include <stdio.h>
#include <stdlib.h>

struct process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int pr;
};

void main()
{
    int n;

    printf("Enter the no of processes: ");
    scanf("%d",&n);

    struct process p[n];

    printf("\nEnter the process id,at,bt,pr");
    for(int i=0;i<n;i++)
    {
        scanf("%d%d%d%d",&p[i].pid,&p[i].at,&p[i].bt,&p[i].pr);
    }

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(p[j].at>p[j+1].at || (p[j].at>p[j+1].at && p[j].pid>p[j+1].pid ))
            {
                struct process temp = p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }

    int completed=0,time=0;

    while(completed<n)
    {
        int count=0;
        for(int i=completed;i<n;i++)
        {
            if(p[i].at<=time)
            {
                count++;
            }
        }
        if(count==0)
        {
            time=p[completed].at;
        }
        if(count>1)
        {
            for(int i=completed;i<completed+count;i++)
            {
                for(int j=completed;j<completed+count-1;j++)
                {
                    if(p[j].pr>p[j+1].pr)
                    {
                        struct process temp = p[j];
                        p[j]=p[j+1];
                        p[j+1]=temp;
                    }
                }
            }
        }
        if(p[completed].at>time)
        {
            time=p[completed].at;
        }
        time=time+p[completed].bt;
        p[completed].ct=time;
        p[completed].tat=p[completed].ct-p[completed].at;
        p[completed].wt=p[completed].tat-p[completed].bt;
        completed++;
    }


    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if( p[j].pid>p[j+1].pid )
            {
                struct process temp = p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    double awt=0,atat=0;
    printf("\nPid\tAt\tBt\tCt\tTat\tWt\n");
    for (int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
        printf("\n");
        awt += p[i].wt;
        atat += p[i].tat;
    }
    awt /= n;
    atat /= n;
    printf("Average Waiting Time: %f\nAverage Turnaround Time: %f\n", awt, atat);

}
