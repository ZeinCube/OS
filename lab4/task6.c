//
// Created by botinok on 13.05.2020.
//

#include <stdlib.h>

//int main(){
static void task6(){
    void *p = malloc(256);
    ((int *)p)[0] = 1;
}