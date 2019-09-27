#ifndef SCHEDULER_SCHEDULER_H
#define SCHEDULER_SCHEDULER_H

#define INITIAL_CAPACITY 2
#define stack_size 1024 * 1024

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

int *copy_file_contents_to_array(char *file_name_ptr,
                                 int *arr, int *size, int *capacity);

void fair_scheduler(ucontext_t ctx[], int coro_cnt, char *fin_flags);

void swap_context(int idx, ucontext_t ctx[]);

void print_array(int *array, int size);

int *merge_sort(int *nsrt, int *srt, unsigned int l_idx, unsigned int r_idx);

void write_array_content_to_file(char *file_name_ptr, int *arr, int *size);

#endif //SCHEDULER_SCHEDULER_H