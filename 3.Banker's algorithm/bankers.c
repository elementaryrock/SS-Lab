#include<stdio.h>

void main() {
    int n, m, i, j, avl[30], max[30][30], d = 0, alloc[30][30];
    
    printf("\n========== BANKER'S ALGORITHM ==========\n");
    
    printf("\nEnter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter number of resources: ");
    scanf("%d", &m);
    
    int T[m];
    printf("\nEnter total instances of each resource:\n");
    for (j = 0; j < m; j++) {
        printf("Resource R%d: ", j);
        scanf("%d", &T[j]);
    }
    
    printf("\nEnter the Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    
    printf("\nEnter the Max Need Matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    for (j = 0; j < m; j++) {
        int c = 0;
        for (i = 0; i < n; i++)
            c = c + alloc[i][j];
        avl[j] = T[j] - c;
    }
    
    int finish[n], safeseq[n], work[n], need[n][m];
    
    for (i = 0; i < m; i++)
        work[i] = avl[i];
    
    for (i = 0; i < n; i++)
        finish[i] = 0;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    
    printf("\n========================================\n");
    printf("SYSTEM STATE ANALYSIS\n");
    printf("========================================\n");
    
    printf("\nAvailable Resources: ");
    for (j = 0; j < m; j++)
        printf("R%d:%d ", j, avl[j]);
    printf("\n");
    
    printf("\nNeed Matrix:\n");
    printf("Process\t");
    for (j = 0; j < m; j++)
        printf("R%d\t", j);
    printf("\n");
    
    for (i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (j = 0; j < m; j++)
            printf("%d\t", need[i][j]);
        printf("\n");
    }
    
    for (int k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    safeseq[d++] = i;
                    for (int a = 0; a < m; a++)
                        work[a] = work[a] + alloc[i][a];
                    finish[i] = 1;
                }
            }
        }
    }
    
    int c = 0;
    for (i = 0; i < n; i++) {
        if (finish[i] == 1)
            c++;
    }
    
    printf("\n========================================\n");
    printf("SAFETY ANALYSIS RESULT\n");
    printf("========================================\n");
    
    if (c == n) {
        printf("\n✓ System is in SAFE state!\n");
        printf("\nSafe Sequence: ");
        for (i = 0; i < n; i++) {
            printf("P%d", safeseq[i]);
            if (i < n-1) printf(" -> ");
        }
        printf("\n\nAll processes can complete successfully!\n");
    } else {
        printf("\n✗ System is in UNSAFE state!\n");
        printf("\nDeadlock may occur. System cannot guarantee\n");
        printf("that all processes will complete successfully.\n");
    }
    
    printf("\n========================================\n");
}