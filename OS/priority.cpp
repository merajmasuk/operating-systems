#include <stdio.h>
#include <algorithm>

struct Process {
   int pid;
   int arrival, burst;
   int priority;
   int init, end;
   int waiting, turnaround;
};

// compares two processes depending on arrival time
bool arrivesEarly (Process one, Process two) {
   return (one.arrival < two.arrival);
}

bool higherPriority (Process one, Process two) {
   if (one.priority >= two.priority) {
        return (one.arrival < two.burst);
   }
   return (one.arrival < two.arrival);
}

// sort according to pid
bool operator < (Process one, Process two) {
   return (one.pid < two.pid);
}

int main() {
   printf("Enter the number of processes: ");
   int n; scanf("%d", &n);
   Process process[n];

   for (int i = 0; i < n; i++) {
      process[i].pid = i+1;
      printf("Enter the arrival time and the burst time of process %d: ", i);
      scanf("%d %d", &process[i].arrival, &process[i].burst);
   }

   // sorts process according to burst time
   std::sort(process, process+n, higherPriority);

   printf("\n");

   // test sort
   /* for (int i = 0; i < n; i++) {
       printf("%d %d %d\n", i, process[i].arrival, process[i].burst);
   } */

   int current = 0;
   for (int i = 0; i < n; i++) {
       process[i].init = std::max(current, process[i].arrival);
       process[i].end = process[i].init + process[i].burst;
       current = process[i].end;
       process[i].waiting = process[i].init - process[i].arrival;
       process[i].turnaround = process[i].waiting + process[i].burst;
   }

   printf("\n");

   printf("Process\tBurst\tArrival\tWaiting\tTurnaround\n");
   std::sort(process, process+n);
   for (int i = 0; i < n; i++) {
       printf("P%d\t%d\t%d\t%d\t%d\n", process[i].pid, process[i].burst, process[i].arrival, process[i].waiting, process[i].turnaround);
   }

   return 0;
}

