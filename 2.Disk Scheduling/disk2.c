#include <stdio.h>
#include <stdlib.h> // For abs()
#include <string.h> // For memcpy()

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
                printf("Order of service: %d ", head);
                for (int i = 0; i < n; i++) {
                    printf("%d ", requests[i]);
                    total += abs(requests[i] - current);
                    current = requests[i];
                }
                printf("\nTotal head movement: %d\n", total);
                break;
            }

            case 2: { // MODIFIED SCAN ALGORITHM
                int left[100], right[100], l = 0, r = 0;
                int seek = 0, temp, direction;

                printf("\n--- SCAN ALGORITHM ---\n");
                
                printf("Enter initial direction (1 for Left, 2 for Right): ");
                scanf("%d", &direction);

                // Partition requests into left and right of the head
                for (int i = 0; i < n; i++) {
                    if (requests[i] < head)
                        left[l++] = requests[i];
                    else
                        right[r++] = requests[i];
                }

                // Sort left array in ascending order
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

                printf("Order of service: %d ", head);
                int current = head;

                if (direction == 1) { // Move left first
                    
                    for (int i = l - 1; i >= 0; i--) {
                        printf("%d ", left[i]);
                        seek += abs(current - left[i]);
                        current = left[i];
                    }

                    
                    printf("0 ");
                    seek += abs(current - 0);
                    current = 0;

                     (ascending)
                    for (int i = 0; i < r; i++) {
                        printf("%d ", right[i]);
                        seek += abs(current - right[i]);
                        current = right[i];
                    }

                } else { // Move right first
                    // Service right side (ascending)
                    for (int i = 0; i < r; i++) {
                        printf("%d ", right[i]);
                        seek += abs(current - right[i]);
                        current = right[i];
                    }

                    // Go to the final boundary (disk_size - 1)
                    printf("%d ", disk_size - 1);
                    seek += abs(current - (disk_size - 1));
                    current = disk_size - 1;

                    // Service left side (descending)
                    for (int i = l - 1; i >= 0; i--) {
                        printf("%d ", left[i]);
                        seek += abs(current - left[i]);
                        current = left[i];
                    }
                }

                printf("\nTotal seek distance: %d\n", seek);
                break;
            }


            case 3: {
                int queue[103], temp_req[100];
                int size, pos = -1, seek = 0, temp;

                // Copy requests to a temporary array to not modify the original
                memcpy(temp_req, requests, n * sizeof(int));

                // Add head, 0, and disk_size-1 to the queue for sorting
                temp_req[n] = head;
                temp_req[n+1] = 0;
                temp_req[n+2] = disk_size - 1;
                size = n + 3;

                // Sort the queue to handle all points in order
                for (int i = 0; i < size - 1; i++) {
                    for (int j = 0; j < size - i - 1; j++) {
                        if (temp_req[j] > temp_req[j + 1]) {
                            temp = temp_req[j];
                            temp_req[j] = temp_req[j + 1];
                            temp_req[j + 1] = temp;
                        }
                    }
                }
                
                // Remove duplicates after sorting
                int k = 0;
                for(int i = 0; i < size-1; i++) {
                    if (temp_req[i] != temp_req[i+1]) {
                        queue[k++] = temp_req[i];
                    }
                }
                queue[k++] = temp_req[size-1];
                size = k;


                // Find the position of the head
                for (int i = 0; i < size; i++) {
                    if (queue[i] == head) {
                        pos = i;
                        break;
                    }
                }

                printf("\n--- C-SCAN ALGORITHM ---\n");
                printf("Order of service: ");
                
                // Move from head to the end of the disk
                for (int i = pos; i < size; i++) {
                    printf("%d ", queue[i]);
                }
                
                // Jump to the beginning and service remaining requests
                for (int i = 0; i < pos; i++) {
                    printf("%d ", queue[i]);
                }
                
                // Calculate seek time
                // (head -> disk_size-1) + (disk_size-1 -> 0) + (0 -> request before head)
                if (pos != 0) { // If head is not 0
                    seek = (disk_size - 1 - head) + (disk_size - 1 - 0) + (queue[pos-1] - 0);
                } else { // If head is 0
                    seek = disk_size - 1;
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
