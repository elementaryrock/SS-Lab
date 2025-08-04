#include <stdio.h>

int allocation[10][10];
int max_need[10][10];
int available[10];
int need[10][10];
int n, m;

void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max_need[i][j] - allocation[i][j];
        }
    }
}

int isSafeState() {
    int work[10];
    int finish[10] = {0};
    int safe_sequence[10];
    int count = 0;
    
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    
    while (count < n) {
        int found = 0;
        
        for (int p = 0; p < n; p++) {
            if (finish[p] == 0) {
                int can_allocate = 1;
                for (int j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }
                
                if (can_allocate) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[p][k];
                    }
                    
                    safe_sequence[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        
        if (found == 0) {
            printf("System is in UNSAFE state!\n");
            return 0;
        }
    }
    
    printf("System is in SAFE state.\n");
    printf("Safe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safe_sequence[i]);
    }
    printf("\n");
    return 1;
}

int requestResources(int process_id, int request[]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[process_id][i]) {
            printf("Error: Process has exceeded its maximum claim!\n");
            return 0;
        }
        if (request[i] > available[i]) {
            printf("Resources not available. Process must wait.\n");
            return 0;
        }
    }
    
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }
    
    if (isSafeState()) {
        printf("Request granted successfully!\n");
        return 1;
    } else {
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
        printf("Request denied to maintain system safety!\n");
        return 0;
    }
}

void displayState() {
    printf("\n=== CURRENT SYSTEM STATE ===\n");
    
    printf("\nAllocation Matrix:\n");
    printf("Process\t");
    for (int i = 0; i < m; i++) {
        printf("R%d\t", i);
    }
    printf("\n");
    
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++) {
            printf("%d\t", allocation[i][j]);
        }
        printf("\n");
    }
    
    printf("\nMax Need Matrix:\n");
    printf("Process\t");
    for (int i = 0; i < m; i++) {
        printf("R%d\t", i);
    }
    printf("\n");
    
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++) {
            printf("%d\t", max_need[i][j]);
        }
        printf("\n");
    }
    
    printf("\nNeed Matrix:\n");
    printf("Process\t");
    for (int i = 0; i < m; i++) {
        printf("R%d\t", i);
    }
    printf("\n");
    
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++) {
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }
    
    printf("\nAvailable Resources: ");
    for (int i = 0; i < m; i++) {
        printf("R%d:%d ", i, available[i]);
    }
    printf("\n");
}

int main() {
    printf("=== BANKER'S ALGORITHM IMPLEMENTATION ===\n\n");
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);
    
    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    printf("\nEnter Max Need Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max_need[i][j]);
        }
    }
    
    printf("\nEnter Available Resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
    
    calculateNeed();
    displayState();
    
    printf("\n=== CHECKING INITIAL SAFETY ===\n");
    isSafeState();
    
    int choice;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Make a resource request\n");
        printf("2. Display current state\n");
        printf("3. Check system safety\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int process_id;
                int request[10];
                
                printf("Enter process ID (0 to %d): ", n-1);
                scanf("%d", &process_id);
                
                if (process_id < 0 || process_id >= n) {
                    printf("Invalid process ID!\n");
                    break;
                }
                
                printf("Enter resource request for P%d: ", process_id);
                for (int i = 0; i < m; i++) {
                    scanf("%d", &request[i]);
                }
                
                requestResources(process_id, request);
                break;
            }
            case 2:
                displayState();
                break;
            case 3:
                isSafeState();
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);
    
    return 0;
}