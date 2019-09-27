#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

void swap_context(int idx, ucontext_t ctx[]) {
    int next_coro_idx = 0;
    printf("coro: switching to scheduler\n");
    if (swapcontext(&ctx[idx], &ctx[next_coro_idx]) == -1)
        handle_error("swapcontext");
}

static void _swap_context(int idx, ucontext_t ctx[]) {
    printf("main: next coroutine is №%d\n", idx);
    if (swapcontext(&ctx[0], &ctx[idx]) == -1)
        handle_error("swapcontext");
}

void fair_scheduler(ucontext_t ctx[], int coro_cnt, char *fin_flags) {
    while (1) {
        int fin_cntr = 1;
        for (int i = 1; i < coro_cnt; i++) {
            int x = fin_flags[i];
            if (fin_flags[i] == 0) {
                _swap_context(i, ctx);
            }
            else {
                fin_cntr++;
            }
        }
        if (fin_cntr >= coro_cnt) {
            printf("main: all coroutines has ended\n");
            break;
        }
    }
}