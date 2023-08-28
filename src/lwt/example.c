#include "chloros.h"

#include <stdio.h>
#include <stdlib.h>

void worker(void* arg) {
    int num = *((int*) arg);

    for (int i = 0; i < 10; i++) {
        printf("hello from worker %d\n", num);
        thread_yield();
    }

    free(arg);
}

int main() {
    thread_init();
    for (int i = 0; i < 4; i++) {
        int* num = malloc(sizeof(int));
        *num = i;
        thread_spawn(&worker, num);
    }

    thread_wait();

    return 0;
}
