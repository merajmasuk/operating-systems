#include <stdio.h>
#include <limits.h>
#include <algorithm>

struct Process {
   int pid;
   int arrival, burst;
   int init, end;
   int waiting, turnaround;
};

// sort according to pid
bool operator < (Process one, Process two) {
   return (one.pid < two.pid);
}

int main() {
   printf("Enter the number of processes: ");
   int n; scanf("%d", &n);
   Process process[n];

   int remaining[n];
   for (int i = 0; i < n; i++) {
      process[i].pid = i+1;
      printf("Enter the arrival time and the burst time of process %d: ", i);
      scanf("%d %d", &process[i].arrival, &process[i].burst);
      remaining[i] = process[i].burst;
   }

   printf("\n");

   // test sort
   /* for (int i = 0; i < n; i++) {
       printf("%d %d %d\n", i, process[i].arrival, process[i].burst);
   } */
  
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;
  
    while (complete != n) {
  
        for (int j = 0; j < n; j++) {
            if ((process[j].arrival <= t) &&
            (remaining[j] < minm) && remaining[j] > 0) {
                minm = remaining[j];
                shortest = j;
                check = true;
            }
        }
  
        if (check == false) {
            t++;
            continue;
        }
  
        // Reduce remaining time by one
        remaining[shortest]--;
  
        // Update minimum
        minm = remaining[shortest];
        if (minm == 0)
            minm = INT_MAX;
  
        // If a process gets completely
        // executed
        if (remaining[shortest] == 0) {
  
            // Increment complete
            complete++;
            check = false;
  
            // Find finish time of current
            // process
            finish_time = t + 1;
  
            // Calculate waiting time
            process[shortest].waiting = finish_time -
                        process[shortest].burst -
                        process[shortest].arrival;
  
            if (process[shortest].waiting < 0)
                process[shortest].waiting = 0;
        }
        // Increment time
        t++;
    }

   printf("\n");

   printf("Process\tBurst\tArrival\tWaiting\tTurnaround\n");
   // std::sort(process, process+n);
   for (int i = 0; i < n; i++) {
       printf("P%d\t%d\t%d\t%d\t%d\n", process[i].pid, process[i].burst, process[i].arrival, process[i].waiting, process[i].waiting + process[i].burst);
   }

   return 0;
}

