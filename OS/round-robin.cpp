#include <stdio.h>
#include <algorithm>

struct Process {
   int pid;
   int arrival, burst;
   int init, end;
   int waiting, turnaround;
};

// compares two processes depending on arrival time
bool arrivesEarly (Process one, Process two) {
   return (one.arrival < two.arrival);
}

// sort according to pid
bool operator < (Process one, Process two) {
   return (one.pid < two.pid);
}

int main() {
   printf("Enter time quantum: ");
   int quantum; scanf("%d", &quantum);

   printf("Enter the number of processes: ");
   int n; scanf("%d", &n);
   Process process[n];

   for (int i = 0; i < n; i++) {
      process[i].pid = i+1;
      printf("Enter the arrival time and the burst time of process %d: ", i);
      scanf("%d %d", &process[i].arrival, &process[i].burst);
   }

   printf("\n");

   // test sort
   /* for (int i = 0; i < n; i++) {
       printf("%d %d %d\n", i, process[i].arrival, process[i].burst);
   } */

   int remain[n];
    for (int i = 0 ; i < n ; i++) {
        remain[i] = process[i].burst;
    }
 
    int t = 0; // Current time
 
    while (1) {
        bool done = true;
 
        for (int i = 0 ; i < n; i++) {
            if (remain[i] > 0) {
                done = false;
 
                if (remain[i] > quantum) {
                    t += quantum;
                    remain[i] -= quantum;
                } else {
                    t = t + remain[i];
                    process[i].waiting = t - process[i].burst;
                    remain[i] = 0;
                }
            }
        }
 
        if (done == true)
        break;
    }

   printf("\n");

   printf("Process\tBurst\tArrival\tWaiting\tTurnaround\n");
   std::sort(process, process+n);
   for (int i = 0; i < n; i++) {
       printf("P%d\t%d\t%d\t%d\t%d\n", process[i].pid, process[i].burst, process[i].arrival, process[i].waiting, process[i].waiting+process[i].burst);
   }

   return 0;
}

