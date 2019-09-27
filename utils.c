#include <stdio.h>
#include <stdlib.h>

void print_array(int *array, int size) {
    for (int i = 0 ; i < size; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
}


int *push(int *arr, int index, int value, int *size, int *capacity){
    int *new_arr = NULL;
    if(*size >= *capacity){
        new_arr = realloc(arr, sizeof(int) * *size * 2);
        if(!new_arr) {
            printf("Can not reallocate memory");
            exit(1);
        }
        *capacity = *size * 2;
    }

    new_arr = new_arr ? new_arr : arr;
    new_arr[index] = value;
    *size = *size + 1;
    return new_arr;
}


int *copy_file_contents_to_array(char *file_name_ptr,
        int *arr, int *size, int *capacity) {
    FILE *fp;

    if((fp=fopen(file_name_ptr, "r"))==NULL) {
        printf ("Cannot open file.\n");
        exit(0);
    }

    int val = 0;
    for (int i = 0; !feof(fp); i++) {
        fscanf(fp,"%d", &val);
        arr = push(arr, i, val, size, capacity);
    }
    fclose(fp);
    return arr;
}


void write_array_content_to_file(char *file_name_ptr, int *arr, int *size) {
    FILE *fp;

    if((fp=fopen(file_name_ptr, "a"))==NULL) {
        printf ("Cannot open file.\n");
        exit(0);
    }

    for (int i = 0; i < *size; i++) {
        fprintf(fp,"%d ", *arr);
        *arr++;
    }
    fprintf(fp,"\n");
    fclose(fp);
}