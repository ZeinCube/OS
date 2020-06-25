#include <stdio.h>

static int task2() {
    /* Assume name shorter than 20 chars. */
    char name[20]; // заводим массив символов
    puts("Enter name: "); // выводим строку
    scanf("%19s", name); // считываем ответ < 19 символов (последний символ отводится под конец строки)
    printf("Hello,  %s.\n\n\tNice to see you.\n", name); // выводим считанное имя с сообщением

    puts("Enter name: "); // выводим строку
    scanf("%19s", name); //считываем в ту же самую переменную ещё раз. (Оно перезапишется)

    // выводим считанное имя с сообщением с enter и tab
    printf("Hello,  %s.\n\n\tNice to see you.\n", name);

    char *name1 = "Anna"; // указатель присваиваем ему указатель на первый элемент строки “Anna”
    char a_letter = name1[0]; // присваиваем первый символ name1 ("A")

    name1[0] = name1[3];//пытаемся заменить первый символ на последний (annA)
    //получаем ошибку, так как попытались изменить константную строку, которая
    //хранится в области памяти доступной только для чтения => программа выдаст ошибку Segmentation fault

    name1[3] = a_letter;
    puts(name1);

    return 0;
}