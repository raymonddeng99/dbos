#include "chloros.h"

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int counter;

void worker_with_arith(void* arg) {
    (void) arg;

    float a = 42;
    counter = sqrt(a);
}

static void check_stack_align(void) {
    thread_spawn(worker_with_arith, NULL);
    assert(counter == 6);
}

#define NLOOPS 100
int loop_values[NLOOPS * 2];
size_t loop_idx;

static void push_back(int i) {
    loop_values[loop_idx++] = i;
}

void worker_yield_loop(void* arg) {
    (void) arg;

    for (int i = 0; i < NLOOPS; i++) {
        push_back(i);
        assert(thread_yield());
    }
}

static void check_yield_loop(void) {
    thread_spawn(worker_yield_loop, NULL);
    thread_spawn(worker_yield_loop, NULL);
    thread_wait();
    assert(loop_idx == NLOOPS * 2);
    for (int i = 0; i < NLOOPS; i++) {
        assert(loop_values[i * 2] == i);
        assert(loop_values[i * 2 + 1] == i);
    }
}

void worker_with_argument(void* arg) {
    counter = *((int*) &arg);
}

static void check_spawn(void) {
    thread_spawn(worker_with_argument, (void*) 42);
    thread_wait();
    assert(counter == 42);
}

void worker(void* arg) {
    (void) arg;

    ++counter;
    assert(thread_yield());
    ++counter;
    thread_yield();
    thread_yield();
}

static void check_yield(void) {
    assert(!thread_yield());
    thread_spawn(worker, NULL);
    assert(counter == 1);
    thread_wait();
    assert(counter == 2);
    assert(!thread_yield());
}

int main(void) {
    thread_init();
    check_yield();
    check_spawn();
    check_stack_align();
    check_yield_loop();
    printf("threads: pass\n");
    return 0;
}
