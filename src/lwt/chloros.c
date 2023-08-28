#include "chloros.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

// The run queue is a doubly linked list of threads. The front and the back of
// the list are tracked here.
static struct thread* runq_front;
static struct thread* runq_back;

// Push a thread onto the front of the run queue.
static void runq_push_front(struct thread* n) {
    n->next = runq_front;
    n->prev = NULL;
    if (runq_front)
        runq_front->prev = n;
    else
        runq_back = n;
    runq_front = n;
}

// Push a thread onto the back of the run queue.
static void runq_push_back(struct thread* n) {
    n->next = NULL;
    n->prev = runq_back;
    if (runq_back)
        runq_back->next = n;
    else
        runq_front = n;
    runq_back = n;
}

// Remove a thread from the run queue.
static void runq_remove(struct thread* n) {
    if (n->next)
        n->next->prev = n->prev;
    else
        runq_back = n->prev;
    if (n->prev)
        n->prev->next = n->next;
    else
        runq_front = n->next;
}

static uint64_t next_id;

// Use a 2MB stack.
#define STACK_SIZE (1 << 21)

// Corresponds to thread_start in swtch.S.
void thread_start(void);

// Corresponds to ctxswitch in swtch.S.
void ctxswitch(struct context* old, struct context* new);

// The scheduler thread.
static struct thread* scheduler;

// The currently executing thread (or NULL).
static struct thread* running;

// This is the function that the scheduler runs. It should continuously pop a
// new thread from the run queue and attempt to run it.
static void schedule(void* _) {
    (void) _;

    // FIXME: while there are still threads in the run queue, pop the next one
    // and run it. Make sure to adjust 'running' before you switch to it. Once
    // it context switches back to the scheduler by calling yield, you can
    // either put it back in the run queue (if it is still runnable), or
    // destroy it (if it exited).
    //
    // Hint: you can implement this how you like, but you might want to think
    // about what happens when the scheduler first starts up. At that point
    // 'running' might be the initial thread, which should first be put back on
    // the run queue before the main scheduler loop begins.
    assert(!"unimplemented");
}

// Creates a new thread that will execute fn(arg) when scheduled. Return the
// allocated thread, or NULL on failure.
static struct thread* thread_new(threadfn_t fn, void* arg) {
    // FIXME: allocate a new thread. This should give the thread a stack and
    // set up its context so that when you context switch to it, it will start
    // executing fn(arg).
    //
    // Hint: set up the thread so that when it gets context switched for the
    // first time, it will execute thread_start() with 'fn' at the top of the
    // stack, and arg above 'fn'.
    assert(!"unimplemented");

    // You'll want to initialize the context's mxcsr and x87 registers to the
    // following values:
    // t->ctx.mxcsr = 0x1F80;
    // t->ctx.x87 = 0x037F;
}

// Initializes the threading library. This should create the scheduler (a
// thread that executes scheduler(NULL)), and register the caller as a thread.
// Returns true on success and false on failure.
bool thread_init(void) {
    // FIXME: create the scheduler by allocating a new thread for it. You'll
    // want to store the newly allocated scheduler in 'scheduler'.
    assert(!"unimplemented");

    // FIXME: register the initial thread (the currently executing context) as
    // a thread. It just needs a thread object but doesn't need a stack or any
    // initial context as it is already running. Make sure to update 'running'
    // since it is already running.
    assert(!"unimplemented");
}

// Spawn a new thread. This should create a new thread for executing fn(arg),
// and switch to it immediately (push it on the front of the run queue, and
// switch to the scheduler).
bool thread_spawn(threadfn_t fn, void* arg) {
    // FIXME
    assert(!"unimplemented");
}

// Wait until there are no more other threads.
void thread_wait(void) {
    while (thread_yield()) {}
}

// Yield the currently executing thread. Returns true if it yielded to some
// other thread, and false if there were no other threads to yield to. If
// there are other threads, this should yield to the scheduler.
bool thread_yield(void) {
    assert(running != NULL);
    // FIXME: if there are no threads in the run queue, return false. Otherwise
    // switch to the scheduler so that we can run one of them.
    assert(!"unimplemented");
}

// The entrypoint for a new thread. This should call the requested function
// with its argument, and then do any necessary cleanup after the function
// completes (to cause the thread to exit).
void thread_entry(threadfn_t fn, void* arg) {
    fn(arg);
    running->state = STATE_EXITED;
    thread_yield();
    // this should never happen
    assert(!"exited thread resumed");
}
