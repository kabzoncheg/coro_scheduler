#include <ucontext.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "scheduler.h"

static void *allocate_stack() {
    void *stack = malloc(stack_size);
    stack_t ss;
    ss.ss_sp = stack;
    ss.ss_size = stack_size;
    ss.ss_flags = 0;
    sigaltstack(&ss, NULL);
    return stack;
}

static void coro_sort(char *argv[], int idx, ucontext_t ctx[], char *fin_flags) {
    printf("coro: coroutine №%d: started\n", idx);
    int *arr = malloc(INITIAL_CAPACITY * sizeof(int));
    int arr_size = 0;
    int arr_capacity = INITIAL_CAPACITY;
    arr = copy_file_contents_to_array(argv[idx], arr, &arr_size, &arr_capacity);

    swap_context(idx, ctx);

    int *arr_srt = malloc(arr_size * sizeof(int));
    print_array(arr, arr_size);
    merge_sort(arr, arr_srt, 0, arr_size - 1);
    print_array(arr, arr_size);

    swap_context(idx, ctx);

    char out_fname[] = "output.txt";
    write_array_content_to_file(out_fname, arr, &arr_size);
    printf("coro: coroutine №%d: ended\n", idx);

    fin_flags[idx] = 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        handle_error("Not enough arguments");
    }

    char coro_flags[argc];
    memset(coro_flags, 0, argc);
    // Storage for coroutines stack
    ucontext_t ctx[argc];
    for (int i = 1; i < argc; i++) {
        char *func_stack = allocate_stack();
        // Initialization of coroutine structures.
        if (getcontext(&ctx[i]) == -1)
            handle_error("getcontext");
        // Specify a stack for each coro
        ctx[i].uc_stack.ss_sp = func_stack;
        ctx[i].uc_stack.ss_size = stack_size;
        // When 'funcX' is finished, it should
        // switch to 'ctx[0]' - main context.
        ctx[i].uc_link = &ctx[0];
        makecontext(&ctx[i], coro_sort, 4, argv, i, ctx, coro_flags);
    }
    fair_scheduler(ctx, argc, coro_flags);
    printf("main: exiting\n");
    return 0;
}