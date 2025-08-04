#include <stdio.h>
#include <stdlib.h>

void main() {
    int requests[100], n, head, disk_size, choice;
    
    printf("\n========== DISK SCHEDULING ALGORITHMS ==========\n");
    
    printf("\nEnter number of requests: ");
    scanf("%d", &n);
    
    printf("Enter request sequence:\n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }
    
    printf("Enter initial head position: ");
    scanf("%d", &head);
    
    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    
    do {
        printf("\n=======================================\n");
        printf("DISK SCHEDULING MENU\n");
        printf("=======================================\n");
        printf("1. FCFS (First Come First Serve)\n");
        printf("2. SCAN (Elevator Algorithm)\n");
        printf("3. C-SCAN (Circular SCAN)\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int total = 0, current = head;
                printf("\n--- FCFS ALGORITHM ---\n");
                printf("Order of service: ");
                for (int i = 0; i < n; i++) {
                    printf("%d ", requests[i]);
                    total += abs(requests[i] - current);
                    current = requests[i];
                }
                printf("\nTotal head movement: %d\n", total);
                break;
            }
            
            case 2: {
                int left[100], right[100], l = 0, r = 0;
                int seek = 0, temp;
                
                for (int i = 0; i < n; i++) {
                    if (requests[i] < head)
                        left[l++] = requests[i];
                    else
                        right[r++] = requests[i];
                }
                
                left[l++] = 0;
                
                for (int i = 0; i < l - 1; i++) {
                    for (int j = 0; j < l - i - 1; j++) {
                        if (left[j] > left[j + 1]) {
                            temp = left[j];
                            left[j] = left[j + 1];
                            left[j + 1] = temp;
                        }
                    }
                }
                
                for (int i = 0; i < r - 1; i++) {
                    for (int j = 0; j < r - i - 1; j++) {
                        if (right[j] > right[j + 1]) {
                            temp = right[j];
                            right[j] = right[j + 1];
                            right[j + 1] = temp;
                        }
                    }
                }
                
                printf("\n--- SCAN ALGORITHM ---\n");
                printf("Order of service: ");
                int current = head;
                
                for (int i = l - 1; i >= 0; i--) {
                    printf("%d ", left[i]);
                    seek += abs(current - left[i]);
                    current = left[i];
                }
                
                for (int i = 0; i < r; i++) {
                    printf("%d ", right[i]);
                    seek += abs(current - right[i]);
                    current = right[i];
                }
                
                printf("\nTotal seek distance: %d\n", seek);
                break;
            }
            
            case 3: {
                int queue[100], size, pos, seek = 0, temp;
                
                for (int i = 0; i < n; i++)
                    queue[i] = requests[i];
                
                queue[n] = head;
                queue[n + 1] = 0;
                queue[n + 2] = disk_size - 1;
                size = n + 3;
                
                for (int i = 0; i < size - 1; i++) {
                    for (int j = 0; j < size - i - 1; j++) {
                        if (queue[j] > queue[j + 1]) {
                            temp = queue[j];
                            queue[j] = queue[j + 1];
                            queue[j + 1] = temp;
                        }
                    }
                }
                
                for (int i = 0; i < size; i++) {
                    if (queue[i] == head) {
                        pos = i;
                        break;
                    }
                }
                
                printf("\n--- C-SCAN ALGORITHM ---\n");
                printf("Order of service: ");
                
                for (int i = pos; i < size; i++) {
                    printf("%d ", queue[i]);
                    if (i != pos)
                        seek += abs(queue[i] - queue[i - 1]);
                }
                
                seek += abs(queue[size - 1] - queue[0]);
                
                for (int i = 0; i < pos; i++) {
                    printf("%d ", queue[i]);
                    if (i != 0)
                        seek += abs(queue[i] - queue[i - 1]);
                }
                
                printf("\nTotal seek distance: %d\n", seek);
                break;
            }
            
            case 4:
                printf("\nExiting program...\n");
                printf("=======================================\n");
                break;
                
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
        
    } while (choice != 4);
}