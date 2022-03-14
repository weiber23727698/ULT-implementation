#include "kernel/types.h"
#include "user/user.h"
#include "user/threads.h"

#define NULL 0
void f4(void *arg)
{
    int i = 1000;

    while(1) {
        printf("thread 4: %d\n", i++);
        if (i == 1001) {
            thread_exit();
        }
        thread_yield();
    }
}

void f2(void *arg)
{
    int i = 10000;

    struct thread *t4 = thread_create(f4, NULL);
    thread_add_runqueue(t4);

    while(1) {
        printf("thread 2: %d\n", i++);
        if (i == 10002) {
            thread_exit();
        }
        thread_yield();
    }
}

void f3(void *arg)
{
    int i = 0;

    while(1) {
        printf("thread 3: %d\n", i++);
        if (i == 3) {
            thread_exit();
        }
        thread_yield();
    }
}

void f1(void *arg)
{
    int i = 100;

    struct thread *t2 = thread_create(f2, NULL);
    thread_add_runqueue(t2);
    struct thread *t3 = thread_create(f3, NULL);
    thread_add_runqueue(t3);
    
    while(1) {
        printf("thread 1: %d\n", i++);
        if (i == 103) {
            thread_exit();
        }
        thread_yield();
    }
}
int main(int argc, char **argv)
{
    printf("mp1-2\n");
    struct thread *t1 = thread_create(f1, NULL);
    thread_add_runqueue(t1);
    thread_start_threading();
    printf("\nexited\n");
    exit(0);
}