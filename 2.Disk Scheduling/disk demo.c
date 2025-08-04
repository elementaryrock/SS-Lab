#include <stdio.h>
#include <stdlib.h>
int requests[100], n, head, disk_size;
void fcfs() {
 int total = 0, current = head;
 printf("\n--- FCFS ---\nOrder of service:\n");
 for (int i = 0; i < n; i++) {
 printf("%d ", requests[i]);
 total += abs(requests[i] - current);
 current = requests[i];
 }
 printf("\nTotal head movement: %d\n", total);
}
void scan() {
 int queue[100], size, i, j, temp, pos;
 int seek = 0;
 int left[100], right[100];
 int l = 0, r = 0;
 for (i = 0; i < n; i++) {
 if (requests[i] < head)
 left[l++] = requests[i];
 else
 right[r++] = requests[i];
 }
 left[l++] = 0;
 for (i = 0; i < l - 1; i++) {
 for (j = 0; j < l - i - 1; j++) {
 if (left[j] > left[j + 1]) {
 temp = left[j];
 left[j] = left[j + 1];
 left[j + 1] = temp;
 }
 }
 }
 for (i = 0; i < r - 1; i++) {
 for (j = 0; j < r - i - 1; j++) {
 if (right[j] > right[j + 1]) {
 temp = right[j];
 right[j] = right[j + 1];
 right[j + 1] = temp;
 }
 }
 }
 printf("\n--- SCAN (Left First) ---\nOrder of 
service:\n");
 int current = head;
 for (i = l - 1; i >= 0; i--) {
 printf("%d ", left[i]);
 seek += abs(current - left[i]);
 current = left[i];
 }
 for (i = 0; i < r; i++) {
 printf("%d ", right[i]);
 seek += abs(current - right[i]);
 current = right[i];
 }
 printf("\nTotal Seek Distance: %d\n", seek);
}
void cscan() {
 int queue[100], size, i, j, temp, pos, seek = 0;
 for (i = 0; i < n; i++)
 queue[i] = requests[i];
 queue[n] = head;
 queue[n + 1] = 0;
 queue[n + 2] = disk_size - 1;
 size = n + 3;
 for (i = 0; i < size - 1; i++) {
 for (j = 0; j < size - i - 1; j++) {
 if (queue[j] > queue[j + 1]) {
 temp = queue[j];
 queue[j] = queue[j + 1];
 queue[j + 1] = temp;
 }
 }
 }
 for (i = 0; i < size; i++) {
 if (queue[i] == head) {
 pos = i;
 break;
 }
 }
 printf("\n--- C-SCAN ---\nOrder of service:\n");
 for (i = pos; i < size; i++) {
 printf("%d ", queue[i]);
 if (i != pos)
 seek += abs(queue[i] - queue[i - 1]);
 }
 seek += abs(queue[size - 1] - queue[0]);
 for (i = 0; i < pos; i++) {
 printf("%d ", queue[i]);
 if (i != 0)
 seek += abs(queue[i] - queue[i - 1]);
 }
 printf("\nTotal Seek Distance: %d\n", seek);
}
int main() {
 int choice;
 printf("Enter number of requests: ");
 scanf("%d", &n);
 printf("Enter request sequence:\n");
 for (int i = 0; i < n; i++)
 scanf("%d", &requests[i]);
 printf("Enter initial head position: ");
 scanf("%d", &head);
 printf("Enter disk size (for C-SCAN): ");
 scanf("%d", &disk_size);
 do {
 printf("\n--- Disk Scheduling Menu ---\n");
 printf("1. FCFS\n");
 printf("2. SCAN\n");
 printf("3. C-SCAN\n");
 printf("4. Exit\n");
 printf("Choose an option: ");
 scanf("%d", &choice);
 switch (choice) {
 case 1: fcfs(); break;
 case 2: scan(); break;
 case 3: cscan(); break;
 case 4: printf("Exiting...\n"); break;
 default: printf("Invalid choice. Try again.\n");
 }
 } while (choice != 4);
 return 0;
}