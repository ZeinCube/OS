Лабораторная работа № 4
Использование виртуальной памяти. Выявление ошибок с использованием gdb и valgrind.

1)В программу aspace.c добавить malloc() и выяснить в каком направлении происходит 
добавление динамической памяти (к старшим адресам). Добавить локальную переменную 
и проверить то, что в стеке адреса задействуются в сторону убывания. Как найти 
адрес указателя? Что возвращается при оценивании p и &p?

"В программу aspace.c добавить malloc()"
-Указатель назовем p2.

"Добавить локальную переменную"
-назовем ее local2 

    "выяснить в каком направлении происходит добавление динамической памяти"

Проверим, что добавление динамической памяти происходит к старшим адресам. 
Напечатаем адрес указателя, который вернул malloc. 

У переменной p2 адрес больше, чем у p => добавление динамической памяти 
происходит к старшим адресам. 

    "проверить то, что в стеке адреса задействуются в сторону убывания"

Помним, что переменная local2 была объявлена позже, чем local. 

У переменной local2 адрес больше, чем у local => адрес тоже увеличивается.

    "Как найти адрес указателя? Что возвращается при оценивании p и &p?"

Адрес указателя можно получить с помощью оператора "амперсанд": &pointer.
&p вернёт адрес, где лежит указатель, в то время как p вернёт сам указатель.


2) Объяснить поведение фрагмента кода для переменных name и name1


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
    хранится в области памяти доступной только для чтения => программа выдаст ошибку Segmentation fault
    
    name1[3] = a_letter;
    puts(name1); 

3) Разработать программу null.c, которая создает указатель на целое и устанавливает его в NULL
Затем она пытается получить значение переменной по указателю (dereference). 
Объяснить результат запуска откомпилированной программы.
 
создали указатель типа int на NULL
 
    printf("%d", *a); // пытаемся обратиться к нему и напечатать значение
    
но получаем ошибку sigsegv - сигнал, посылаемый процессу при попытке обращения к 
несуществующей памяти или обращения с нарушением прав доступа. 
 
4) Откомпилировать null.c с ключом -g, запустить dbg null и вызвать команду run. 
Объяснить реакцию отладчика. 

    gcc -g null.c -o null
    
    gdb null
    (gdb) run

Это связано с тем, что мы пытаемся обратиться к нулевому указателю,
получаем ошибку sigsegv- сигнал, посылаемый процессу при попытке обращения к 
несуществующей памяти или обращения с нарушением прав доступа.

5) Установить и использовать valgrind (memcheck) для анализа ситуации из 4: 
valgrind --leak-check=yes null 
(valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose 
--log-file=valgrind-out.txt null). Объяснить результат.

Здесь мы так же видим ошибку Segmentation fault, т.к. пытаемся обратиться к 
значению по нулевому указателю. 

6) Написать простую программу, которая использует malloc(), но не освобождает 
память по завершению. Использовать gdb и valgrind для того, чтобы объяснить ошибку.

Что через gdb, что через valgrind видим утечку памяти.
Она появилась из-за того, что мы не освободили память, выделенную через malloc.

7) Написать программу, которая создает массив целых data размера 100, 
используя malloc(). Установить data[100] в 0. Запустить программу и 
найти ошибку (если есть) с помощью valgrind.

Видим две ошибки. Первая связана с тем, что мы пытаемся записать 
значение в память, которую не выделили т.е. мы пытаемся обратиться 
к памяти, которая расположена после выделенного нами блока. Вторая 
ошибка связана оппять с тем же, что мы не очищаем использованную 
память и получаем утечку

8) Написать программу, которая создает массив целых (как в 7),
освобождает его и пытается напечатать значение какого-либо элемента. 
Диагностировать ошибку с использованием valgrind.

По результатам выполнения программы valgrind обнаружил ошибку,
которая сообщает о том, что память, к которой мы пытаеся обратиться, уже освобождена.