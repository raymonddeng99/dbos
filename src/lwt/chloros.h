#pragma once

#include <stdbool.h>
#include <stdint.h>

// Thread execution context: all callee-saved registers. Note that there is no
// instruction pointer; where does that get saved?
struct context {
    uint64_t rsp;
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t rbx;
    uint64_t rbp;
    uint32_t mxcsr;
    uint32_t x87;
};

enum state {
    STATE_RUNNABLE,
    STATE_EXITED,
};

// A thread has a state, an ID, a context and a stack.
struct thread {
    uint64_t id;
    enum state state;
    struct context ctx;

    uint8_t* stack;

    // Nodes for the scheduler's run queue.
    struct thread* next;
    struct thread* prev;
};

typedef void (*threadfn_t)(void*);

// Initializes the thread library. Registers the initial thread as a thread,
// and the scheduler.
bool thread_init(void);
// Spawn a new thread that calls fn(arg). Returns true on success, and false on
// failure.
bool thread_spawn(threadfn_t fn, void* arg);
// Yield the current thread.
bool thread_yield(void);
// Wait for all spawned threads to complete. Should only be called from the
// initial thread.
void thread_wait(void);
