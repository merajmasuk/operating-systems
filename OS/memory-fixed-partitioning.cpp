#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process {
    int size, flag;
};

struct block {
    int size, flag;
};

int tmpblock[100000];

void input(process p[], block b[], int *n, int *m) {
    printf("Blocks number: ");
    scanf("%d", m);
    printf("Enter Block size:\n");

    for(int i=0; i<*m; i++) {
        printf(" Block %d : ", i+1);
        scanf("%d", &b[i].size);
        tmpblock[i]=b[i].size;
    }

    printf("Processes number: ");
    scanf("%d", n);
    printf("Enter Process size:\n");

    for(int i=0; i<*n; i++) {
        printf("Process %d : ", i+1);
        scanf("%d", &p[i].size);
    }
}

void init(process p[], block b[], int n, int m) {
    for (int i=0; i<n; i++) {
        p[i].flag=0;
    }
    for (int i=0; i<m; i++) {
        b[i].flag=0;
        b[i].size=tmpblock[i];
    }
}

void first_fit(process p[], block b[], int n, int m) {
    int in=0, ex=0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (p[i].size <= b[j].size && b[j].flag == 0 && p[i].flag == 0) {
                b[j].flag = p[i].flag = 1;
                in += b[j].size - p[i].size;
                printf("P %d\t-\tB %d  = %d\n",i+1,j+1, b[j].size - p[i].size);
                b[j].size -= p[i].size;
                break;
            }
        }
        if (p[i].flag == 0) {
            printf("P %d\t-\tUnassigned\n",i+1);
        }
    }

    printf("\n");
    printf("Total internal fragmentation : %d\n", in);

    for (int j=0; j<m; j++) {
        if (b[j].flag == 0) {
            ex+=b[j].size;
        }
    }
    printf("Total external fragmentation : %d\n", ex);
}

void best_fit(process p[], block b[], int n, int m) {
    int in=0, ex=0;
    for (int i=0; i<n; i++) {
        int min=9999, id=9999;
        for (int j=0; j<m; j++) {
            if (p[i].size <= b[j].size && b[j].flag == 0 && min > (b[j].size - p[i].size)) {
                min = b[j].size - p[i].size;
                id = j;
            }
        }
        if (min != 9999) {
            b[id].flag = p[i].flag = 1;
            in += b[id].size - p[i].size;
            printf("P %d\t-\tB %d  = %d\n", i+1, id+1, b[id].size - p[i].size);
            b[id].size -= p[i].size;
        }
        if (p[i].flag == 0) {
            printf("P %d\t-\tUnassigned\n", i+1);
        }
    }
 
    printf("Total internal fragmentation : %d\n\n", in);
    for (int j=0; j<m; j++) {
        if(b[j].flag == 0) {
            ex+=b[j].size;
        }
    }
    printf("Total external fragmentation : %d\n", ex);
}

void worst_fit(process p[], block b[], int n, int m) {
    int in=0, ex=0;
 
    for (int i=0; i<n; i++) {
        int max = -1, id=9999;
        for (int j=0; j<m; j++) {
            if (p[i].size <= b[j].size && b[j].flag == 0 && max < (b[j].size - p[i].size)) {
                max = b[j].size - p[i].size;
                id = j;
            }
        }
        if (max != -1) {
            b[id].flag = p[i].flag = 1;
            in += b[id].size - p[i].size;
            printf("P %d\t-\tB %d  = %d\n", i+1, id+1, b[id].size - p[i].size);
            b[id].size-=p[i].size;
        }
        if (p[i].flag == 0) {
            printf("P %d\t-\tUnassigned\n", i+1);
        }
    }

    printf("\n");
    printf("Internal fragmentation : %d\n", in);

    for (int j=0; j<m; j++) {
        if (b[j].flag == 0) {
            ex += b[j].size;
        }
    }
    printf("External fragmentation : %d\n", ex);
}

int main() {
    int ch, n=0, m=0;
    process p[10];
    block b[10];

    do {
        printf("Options:\n");
        printf("1. Input\n");
        printf("2. First Fit\n");
        printf("3. Best Fit\n");
        printf("4. Worst Fit\n");
        printf("5. Exit\n");
        printf("Select : ");
        scanf("%d", &ch);

        if (ch == 1) {
            input(p, b, &n, &m);
        } else if (ch == 2) {
            init(p, b, n, m);
            first_fit(p, b, n, m);
        } else if (ch == 3) {
            init(p, b, n, m);
            best_fit(p, b, n, m);
        } else if (ch == 4) {
            init(p, b, n, m);
            worst_fit(p, b, n, m);
        } else if (ch == 5) {
            break;
        } else {
            printf("Invalid option!\n");
        }
    } while (ch != 4);
    return 0;
}
