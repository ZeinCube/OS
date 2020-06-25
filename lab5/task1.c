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

static void task1() {
    int mem = 300 * 1024;//300КВ
    char buffer[mem];
    set_start_time();//запустили таймер на создание файла
    int f = creat("task1.txt", S_IWRITE);//создаем файл и открываем его для записи
    printf("creat: %ld\n", get_end_time());//остановим таймер на создание и выведем время

    set_start_time();//запустили таймер на запись в файл 300кб
    write(f, buffer, mem);//записали 300кб
    printf("write: %ld\n", get_end_time());//остановим таймер на запись и выведем время

    set_start_time();//запустили таймер на очистку всех записей
    ftruncate(f, 0);//файл не закрывается, но очищается
    printf("ftruncate: %ld\n", get_end_time());//остановим таймер на очистку и выведем время

    set_start_time();//запустили таймер на закрытие файла
    close(f);//закрыли файл
    printf("close: %ld\n", get_end_time());//остановим таймер на закрытие и выведем время

    set_start_time();//запустили таймер на удаление файла
    remove("task1.txt");//удалили
    printf("remove: %ld\n", get_end_time());//остановили

}