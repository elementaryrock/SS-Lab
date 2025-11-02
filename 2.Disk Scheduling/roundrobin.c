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
    int rt;
};

void main()
{
    int n,tq;

    printf("Enter the no of processes: ");
    scanf("%d",&n);

    struct process p[n];

    printf("\nEnter the process id,at,bt,pr");
    for(int i=0;i<n;i++)
    {
        scanf("%d%d%d",&p[i].pid,&p[i].at,&p[i].bt);
        p[i].rt=p[i].bt;
    }

    printf("Enter time quantum:");
    scanf("%d",&tq);

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

    int completed=0,time=0,current_time;

    while(completed<n)
    {
        int done=1;
        for(int i=0;i<n;i++)
        {
            if(p[i].rt>0 && p[i].at<=current_time)
            {
                done=0;
                if(p[i].rt>tq)
                {
                    p[i].rt-=tq;
                    current_time+=tq;
                }
                else
                {
                    current_time+=p[i].rt;
                    p[i].ct=current_time;
                    p[i].tat=p[i].ct-p[i].at;
                    p[i].wt=p[i].tat-p[i].bt;
                    p[i].rt=0;
                    completed++;
                }
            }
        }
        if(done)
        {
            current_time++;
        }
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
