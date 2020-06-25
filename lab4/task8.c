//
// Created by botinok on 14.05.2020.
//

#include <stdio.h>
#include <stdlib.h>

//int main(){
static void task8(){
    int *data = malloc(100 * sizeof(int));
    data[1] = 1;
    free(data);
    printf("%i", data[1]);
}