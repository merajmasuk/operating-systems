#include <stdio.h>
int main() {
    int ms, mp[10];
    char ch = 'y';

    printf("Enter the total memory available (in Bytes) -- ");
    scanf("%d", &ms);

    int temp=ms, i, n=0;
    for (i=0; ch == 'y'; i++, n++) {
        printf("Enter memory required for process %d (in Bytes) -- ",i+1);
        scanf("%d", &mp[i]);
        if (mp[i] <= temp) {
            printf("Memory is allocated for Process %d\n",i+1);
            temp = temp-mp[i];
        } else {
            printf("Memory is Full!\n");
            break;
        }
        printf("Do you want to continue(y/n) -- ");
        scanf(" %c", &ch);
    }

    printf("\n\n");
    printf("Total Memory Available -- %d\n\n", ms);
    printf("\tPROCESS\t\t MEMORY ALLOCATED\n");

    for (i=0; i<n; i++) {
        printf("\n \t%d\t\t%d",i+1,mp[i]);
    }

    printf("\n\n");
    printf("Total Memory Allocated is %d\n", ms-temp);
    printf("Total External Fragmentation is %d\n", temp);
}
