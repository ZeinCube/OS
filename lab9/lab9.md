Лабораторная работа №9 
Обнаружение и устранение проблем в многопотоковых программах с 
использованием helgrind (http://valgrind.org/docs/manual/hg-manual.htm) 
см. также http://www.ostep.org

2. С помощью helgrind (valgrind --tool=helgrind main-race) в программе main-race.c 
проанализировать ошибки в коде, связанные с несинхронизованностью потоков команд, 
работающих с общими данными (data race), и попытаться их устранить. 

Для начала запустим программу:
    
    valgrind --tool=helgrind ./main-race 

Получаем отчет:

    [botinok@farshMac lab9]$ valgrind --tool=helgrind ./main-race 
    ==13056== Helgrind, a thread error detector
    ==13056== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
    ==13056== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==13056== Command: ./main-race
    ==13056== 
    ==13056== ---Thread-Announcement------------------------------------------
    ==13056== 
    ==13056== Thread #1 is the program's root thread
    ==13056== 
    ==13056== ---Thread-Announcement------------------------------------------
    ==13056== 
    ==13056== Thread #2 was created
    ==13056==    at 0x49BF3C2: clone (in /usr/lib/libc-2.31.so)
    ==13056==    by 0x48A632B: create_thread (in /usr/lib/libpthread-2.31.so)
    ==13056==    by 0x48A7C9B: pthread_create@@GLIBC_2.2.5 (in /usr/lib/libpthread-2.31.so)
    ==13056==    by 0x4840677: pthread_create_WRK (hg_intercepts.c:427)
    ==13056==    by 0x109443: Pthread_create (in /home/botinok/CLionProjects/untitled2/lab9/main-race)
    ==13056==    by 0x109531: main (in /home/botinok/CLionProjects/untitled2/lab9/main-race)
    ==13056== 
    ==13056== ----------------------------------------------------------------
    ==13056== 
    ==13056==  Lock at 0x10C0A0 was first observed
    ==13056==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
    ==13056==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-race)
    ==13056==    by 0x1094D4: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-race)
    ==13056==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
    ==13056==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
    ==13056==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
    ==13056==  Address 0x10c0a0 is 0 bytes inside data symbol "m"
    ==13056== 
    ==13056== Possible data race during read of size 4 at 0x10C0C8 by thread #1
    ==13056== Locks held: none
    ==13056==    at 0x109532: main (in /home/botinok/CLionProjects/untitled2/lab9/main-race)
    ==13056== 
    ==13056== This conflicts with a previous write of size 4 by thread #2
    ==13056== Locks held: 1, at address 0x10C0A0
    ==13056==    at 0x1094DE: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-race)
    ==13056==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
    ==13056==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
    ==13056==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
    ==13056==  Address 0x10c0c8 is 0 bytes inside data symbol "balance"
    ==13056== 
    ==13056== ----------------------------------------------------------------
    ==13056== 
    ==13056==  Lock at 0x10C0A0 was first observed
    ==13056==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
    ==13056==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-race)
    ==13056==    by 0x1094D4: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-race)
    ==13056==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
    ==13056==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
    ==13056==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
    ==13056==  Address 0x10c0a0 is 0 bytes inside data symbol "m"
    ==13056== 
    ==13056== Possible data race during write of size 4 at 0x10C0C8 by thread #1
    ==13056== Locks held: none
    ==13056==    at 0x10953B: main (in /home/botinok/CLionProjects/untitled2/lab9/main-race)
    ==13056== 
    ==13056== This conflicts with a previous write of size 4 by thread #2
    ==13056== Locks held: 1, at address 0x10C0A0
    ==13056==    at 0x1094DE: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-race)
    ==13056==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
    ==13056==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
    ==13056==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
    ==13056==  Address 0x10c0c8 is 0 bytes inside data symbol "balance"
    ==13056== 
    ==13056== 
    ==13056== Use --history-level=approx or =none to gain increased speed, at
    ==13056== the cost of reduced accuracy of conflicting-access information
    ==13056== For lists of detected and suppressed errors, rerun with: -s
    ==13056== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

Как видим, есть 2 ошибки, связанные с тем, что переменная
balance в 2 потоках используется одновременно и нет блокирровок

Решение проблемы - добавление блокировки 
    
    Pthread_mutex_lock(&m)
и разблокировки 

    Pthread_mutex_unlock(&m)
мьютекса

Запустим ещё раз: valgrind --tool=helgrind ./main-race 

    [botinok@farshMac lab9]$ valgrind --tool=helgrind ./main-race 
    ==13789== Helgrind, a thread error detector
    ==13789== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
    ==13789== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==13789== Command: ./main-race
    ==13789== 
    ==13789== 
    ==13789== Use --history-level=approx or =none to gain increased speed, at
    ==13789== the cost of reduced accuracy of conflicting-access information
    ==13789== For lists of detected and suppressed errors, rerun with: -s
    ==13789== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 7 from 7)
We did it!


3. В программе main-deadlock.c имеется ошибка, называемая мёртвая 
блокировка (deadlock, ситуация, при которой один поток (поток A), 
ждет ресурса, удерживаемого другим потоком (потоком B), и при этом 
удерживает ресурс, который нужен потоку B. Поскольку потоки A и B 
блокированы в ожидании ресурсов, удерживаемых другим потоком, 
выполнения не происходит). Использовать helgrind и 
проинтерпретировать отчет.

 
        [botinok@farshMac lab9]$ valgrind --tool=helgrind ./main-deadlock 
        ==14467== Helgrind, a thread error detector
        ==14467== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
        ==14467== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
        ==14467== Command: ./main-deadlock
        ==14467== 
        ==14467== ---Thread-Announcement------------------------------------------
        ==14467== 
        ==14467== Thread #3 was created
        ==14467==    at 0x49BF3C2: clone (in /usr/lib/libc-2.31.so)
        ==14467==    by 0x48A632B: create_thread (in /usr/lib/libpthread-2.31.so)
        ==14467==    by 0x48A7C9B: pthread_create@@GLIBC_2.2.5 (in /usr/lib/libpthread-2.31.so)
        ==14467==    by 0x4840677: pthread_create_WRK (hg_intercepts.c:427)
        ==14467==    by 0x109443: Pthread_create (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467==    by 0x109578: main (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467== 
        ==14467== ----------------------------------------------------------------
        ==14467== 
        ==14467== Thread #3: lock order "0x10C0A0 before 0x10C0E0" violated
        ==14467== 
        ==14467== Observed (incorrect) order is: acquisition of lock at 0x10C0E0
        ==14467==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
        ==14467==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467==    by 0x1094F5: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
        ==14467==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
        ==14467==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
        ==14467== 
        ==14467==  followed by a later acquisition of lock at 0x10C0A0
        ==14467==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
        ==14467==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467==    by 0x109501: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
        ==14467==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
        ==14467==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
        ==14467== 
        ==14467== Required order was established by acquisition of lock at 0x10C0A0
        ==14467==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
        ==14467==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467==    by 0x1094DB: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
        ==14467==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
        ==14467==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
        ==14467== 
        ==14467==  followed by a later acquisition of lock at 0x10C0E0
        ==14467==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
        ==14467==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467==    by 0x1094E7: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
        ==14467==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
        ==14467==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
        ==14467== 
        ==14467==  Lock at 0x10C0A0 was first observed
        ==14467==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
        ==14467==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467==    by 0x1094DB: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
        ==14467==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
        ==14467==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
        ==14467==  Address 0x10c0a0 is 0 bytes inside data symbol "m1"
        ==14467== 
        ==14467==  Lock at 0x10C0E0 was first observed
        ==14467==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
        ==14467==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467==    by 0x1094E7: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock)
        ==14467==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
        ==14467==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
        ==14467==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
        ==14467==  Address 0x10c0e0 is 0 bytes inside data symbol "m2"
        ==14467== 
        ==14467== 
        ==14467== 
        ==14467== Use --history-level=approx or =none to gain increased speed, at
        ==14467== the cost of reduced accuracy of conflicting-access information
        ==14467== For lists of detected and suppressed errors, rerun with: -s
        ==14467== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)

Видим ошибку: thread error detector, связана она с тем, что
используется неправильный порядок блокировки.

Как исправить? Убрать if.

    void* worker(void* arg) {
    
        Pthread_mutex_lock(&m1);
        Pthread_mutex_lock(&m2);
        Pthread_mutex_unlock(&m1);
        Pthread_mutex_unlock(&m2);
        return NULL;
    }

4. Также использовать helgrind для main-deadlock-global.c и проанализировать отчет,
 сравнить с предыдущим.
 
    
    [botinok@farshMac lab9]$ valgrind --tool=helgrind ./main-deadlock-global 
    ==16390== Helgrind, a thread error detector
    ==16390== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
    ==16390== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==16390== Command: ./main-deadlock-global
    ==16390== 
    ==16390== ---Thread-Announcement------------------------------------------
    ==16390== 
    ==16390== Thread #3 was created
    ==16390==    at 0x49BF3C2: clone (in /usr/lib/libc-2.31.so)
    ==16390==    by 0x48A632B: create_thread (in /usr/lib/libpthread-2.31.so)
    ==16390==    by 0x48A7C9B: pthread_create@@GLIBC_2.2.5 (in /usr/lib/libpthread-2.31.so)
    ==16390==    by 0x4840677: pthread_create_WRK (hg_intercepts.c:427)
    ==16390==    by 0x109443: Pthread_create (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390==    by 0x109590: main (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390== 
    ==16390== ----------------------------------------------------------------
    ==16390== 
    ==16390== Thread #3: lock order "0x10C0E0 before 0x10C120" violated
    ==16390== 
    ==16390== Observed (incorrect) order is: acquisition of lock at 0x10C120
    ==16390==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
    ==16390==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390==    by 0x109501: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
    ==16390==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
    ==16390==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
    ==16390== 
    ==16390==  followed by a later acquisition of lock at 0x10C0E0
    ==16390==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
    ==16390==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390==    by 0x10950D: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
    ==16390==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
    ==16390==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
    ==16390== 
    ==16390== Required order was established by acquisition of lock at 0x10C0E0
    ==16390==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
    ==16390==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390==    by 0x1094E7: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
    ==16390==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
    ==16390==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
    ==16390== 
    ==16390==  followed by a later acquisition of lock at 0x10C120
    ==16390==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
    ==16390==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390==    by 0x1094F3: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
    ==16390==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
    ==16390==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
    ==16390== 
    ==16390==  Lock at 0x10C0E0 was first observed
    ==16390==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
    ==16390==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390==    by 0x1094E7: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
    ==16390==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
    ==16390==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
    ==16390==  Address 0x10c0e0 is 0 bytes inside data symbol "m1"
    ==16390== 
    ==16390==  Lock at 0x10C120 was first observed
    ==16390==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
    ==16390==    by 0x1092C6: Pthread_mutex_lock (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390==    by 0x1094F3: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-deadlock-global)
    ==16390==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
    ==16390==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
    ==16390==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
    ==16390==  Address 0x10c120 is 0 bytes inside data symbol "m2"
    ==16390== 
    ==16390== 
    ==16390== 
    ==16390== Use --history-level=approx or =none to gain increased speed, at
    ==16390== the cost of reduced accuracy of conflicting-access information
    ==16390== For lists of detected and suppressed errors, rerun with: -s
    ==16390== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)

Получаем такую же ошибку, как в 3 задании (взаимная блокировка),
но, благодаря 
 
     Pthread_mutex_lock(&g);
     
 внешней блокировке, взаимной блокировки не происходит
 
 
 5. В программе main-signal.c переменная (done) используется для того, чтобы 
 обозначить состояние, когда дочерний процесс закончил работу и родительский 
 может продолжить. Проанализировать эффективность и результат работы helgrind 
 на этой программе.
 Запустим
 
 
    [botinok@farshMac lab9]$ gcc main-signal.c -o main-signal -lpthread
    [botinok@farshMac lab9]$ valgrind --tool=helgrind ./main-signal 

Получаем отчет


    ==18058== Helgrind, a thread error detector
    ==18058== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
    ==18058== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==18058== Command: ./main-signal
    ==18058== 
    this should print first
    ==18058== ---Thread-Announcement------------------------------------------
    ==18058== 
    ==18058== Thread #1 is the program's root thread
    ==18058== 
    ==18058== ---Thread-Announcement------------------------------------------
    ==18058== 
    ==18058== Thread #2 was created
    ==18058==    at 0x49BF3C2: clone (in /usr/lib/libc-2.31.so)
    ==18058==    by 0x48A632B: create_thread (in /usr/lib/libpthread-2.31.so)
    ==18058==    by 0x48A7C9B: pthread_create@@GLIBC_2.2.5 (in /usr/lib/libpthread-2.31.so)
    ==18058==    by 0x4840677: pthread_create_WRK (hg_intercepts.c:427)
    ==18058==    by 0x109453: Pthread_create (in /home/botinok/CLionProjects/untitled2/lab9/main-signal)
    ==18058==    by 0x109530: main (in /home/botinok/CLionProjects/untitled2/lab9/main-signal)
    ==18058== 
    ==18058== ----------------------------------------------------------------
    ==18058== 
    ==18058== Possible data race during read of size 4 at 0x10C08C by thread #1
    ==18058== Locks held: none
    ==18058==    at 0x109532: main (in /home/botinok/CLionProjects/untitled2/lab9/main-signal)
    ==18058== 
    ==18058== This conflicts with a previous write of size 4 by thread #2
    ==18058== Locks held: none
    ==18058==    at 0x1094E5: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-signal)
    ==18058==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
    ==18058==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
    ==18058==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
    ==18058==  Address 0x10c08c is 0 bytes inside data symbol "done"
    ==18058== 
    ==18058== ----------------------------------------------------------------
    ==18058== 
    ==18058== Possible data race during write of size 1 at 0x528A1A5 by thread #1
    ==18058== Locks held: none
    ==18058==    at 0x4846526: mempcpy (vg_replace_strmem.c:1537)
    ==18058==    by 0x4941871: _IO_file_xsputn@@GLIBC_2.2.5 (in /usr/lib/libc-2.31.so)
    ==18058==    by 0x4937237: puts (in /usr/lib/libc-2.31.so)
    ==18058==    by 0x109547: main (in /home/botinok/CLionProjects/untitled2/lab9/main-signal)
    ==18058==  Address 0x528a1a5 is 21 bytes inside a block of size 1,024 alloc'd
    ==18058==    at 0x483A7CF: malloc (vg_replace_malloc.c:309)
    ==18058==    by 0x4934BC3: _IO_file_doallocate (in /usr/lib/libc-2.31.so)
    ==18058==    by 0x49435FF: _IO_doallocbuf (in /usr/lib/libc-2.31.so)
    ==18058==    by 0x49427E7: _IO_file_overflow@@GLIBC_2.2.5 (in /usr/lib/libc-2.31.so)
    ==18058==    by 0x49418F5: _IO_file_xsputn@@GLIBC_2.2.5 (in /usr/lib/libc-2.31.so)
    ==18058==    by 0x4937237: puts (in /usr/lib/libc-2.31.so)
    ==18058==    by 0x1094E4: worker (in /home/botinok/CLionProjects/untitled2/lab9/main-signal)
    ==18058==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
    ==18058==    by 0x48A746E: start_thread (in /usr/lib/libpthread-2.31.so)
    ==18058==    by 0x49BF3D2: clone (in /usr/lib/libc-2.31.so)
    ==18058==  Block was alloc'd by thread #2
    ==18058== 
    this should print last
    ==18058== 
    ==18058== Use --history-level=approx or =none to gain increased speed, at
    ==18058== the cost of reduced accuracy of conflicting-access information
    ==18058== For lists of detected and suppressed errors, rerun with: -s
    ==18058== ERROR SUMMARY: 23 errors from 2 contexts (suppressed: 40 from 40)
    [botinok@farshMac lab9]$ 

helgrind сообщает о возможном одновременном использовании переменной 
date и функции printf() сразу в двух потоках. Данный способ ожидания 
потока не является эффективным, т.к. мы просто так тратим в течение 
некоторого времени ресурсы в ожидающем потоке. Более эффективно - использовать
мьютексы.


6. Теперь рассмотреть main-signal-cv.c, которая использует условную 
переменную (condition variable). Сравнить с предыдущей. Проанализировать 
main-signal-cv с использованием helgrind.


    [botinok@farshMac lab9]$ valgrind --tool=helgrind ./main-signal-cv 
    ==18702== Helgrind, a thread error detector
    ==18702== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
    ==18702== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==18702== Command: ./main-signal-cv
    ==18702== 
    this should print first
    this should print last
    ==18702== 
    ==18702== Use --history-level=approx or =none to gain increased speed, at
    ==18702== the cost of reduced accuracy of conflicting-access information
    ==18702== For lists of detected and suppressed errors, rerun with: -s
    ==18702== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 7 from 7)

[ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 7 from 7)]

Данный подход более эффективен, так как используются condition variable, т.е. не расходуются
ресурсы процессора благодаря тому, что поток находится в ожидании до тех пор, пока не придет сигнал.