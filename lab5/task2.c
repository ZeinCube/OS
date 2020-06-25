#include <bits/types/struct_timeval.h>
#include <event.h>
#include <fcntl.h>
#include <zconf.h>
#include <libnet.h>
#include <stdio.h>

struct timeval tv1, tv2, dtv;

static void set_start_time() {
    gettimeofday(&tv1, NULL);
}

static long get_end_time() { //возвр значение в мк сек
    gettimeofday(&tv2, NULL);
    dtv.tv_sec = tv2.tv_sec - tv1.tv_sec;
    dtv.tv_usec = tv2.tv_usec - tv1.tv_usec;
    if (dtv.tv_usec < 0) {
        dtv.tv_sec--;
        dtv.tv_usec += 1000000;
    }

    return dtv.tv_sec * 1000000 + dtv.tv_usec;
}

static void useCreat() { //posix
    char buf = 'C';
    int f = creat("task2.txt", S_IWRITE);
    for (unsigned i = 0; i < 300000; ++i) {
        write(f, &buf, 1);//записали 300,000 однобайтовых записей
    }
    close(f);
}

static void useFopen() {
    char buf = 'F';
    FILE *f = fopen("task2.txt", "w");
    for (unsigned i = 0; i < 300000; ++i) {
        fwrite(&buf, 1, 1, f);//записали    300,000 однобайтовых записей
    }
    //закрыли файл
    fclose(f);
}

static void task2() {
    set_start_time();
    useCreat();
    printf("useCreat: %ld\n", get_end_time());

    set_start_time();
    useFopen();
    printf("useFopen: %ld\n", get_end_time());
    printf("\n");
}
