Лабораторная работа № 11
1)  vector-deadlock.c,  main-common.c и др.:
-Выполнить  ./vector-deadlock -n 2 -l 1 -v
которая инициирует 2 потока  (-n 2) и каждый из них осуществляет одно  сложение (-1 1) с опцией (-v).
Объяснить результат. Меняется ли он от вызова к вызову? 


    [botinok@farshMac lab11]$ gcc vector-deadlock.c -o vector-deadlock -lpthread
    1)[botinok@farshMac lab11]$ ./vector-deadlock -n 2 -l 1 -v
    ->add(0, 1)
    <-add(0, 1)
                  ->add(0, 1)
                  <-add(0, 1)
    2)[botinok@farshMac lab11]$ ./vector-deadlock -n 2 -l 1 -v
    ->add(0, 1)
    <-add(0, 1)
                  ->add(0, 1)
                  <-add(0, 1)
    3)[botinok@farshMac lab11]$ ./vector-deadlock -n 2 -l 1 -v
    ->add(0, 1)
    <-add(0, 1)
                  ->add(0, 1)
                  <-add(0, 1)
    4)[botinok@farshMac lab11]$ ./vector-deadlock -n 2 -l 1 -v
    ->add(0, 1)
    <-add(0, 1)
                  ->add(0, 1)
                  <-add(0, 1)
    5)[botinok@farshMac lab11]$ ./vector-deadlock -n 2 -l 1 -v
    ->add(0, 1)
    <-add(0, 1)
                  ->add(0, 1)
                  <-add(0, 1)
    6)[botinok@farshMac lab11]$ ./vector-deadlock -n 2 -l 1 -v
    ->add(0, 1)
    <-add(0, 1)
                  ->add(0, 1)
                  <-add(0, 1)
    7)[botinok@farshMac lab11]$ ./vector-deadlock -n 2 -l 1 -v
    ->add(0, 1)
    <-add(0, 1)
                  ->add(0, 1)
                  <-add(0, 1)
    8)[botinok@farshMac lab11]$ ./vector-deadlock -n 2 -l 1 -v
                  ->add(0, 1)
                  <-add(0, 1)
    ->add(0, 1)
    <-add(0, 1)
    9)[botinok@farshMac lab11]$ ./vector-deadlock -n 2 -l 1 -v
    ->add(0, 1)
    <-add(0, 1)
                  ->add(0, 1)
                  <-add(0, 1)
    10)[botinok@farshMac lab11]$ ./vector-deadlock -n 2 -l 1 -v
    ->add(0, 1)
    <-add(0, 1)
                  ->add(0, 1)
                  <-add(0, 1)

В 1 из 10 случаев выходные данные отличаются.
Во-первых, это говорит о том, что данная программа не детерминирована 
Во-вторых, это происходит потому, что в функции worker нет блокировок => не определено, 
из какого потока она вызовется сначала => порядок печати результатов непостоянный.


- Добавить флаг  -d и изменить количество циклов  -l .
Всегда ли возникает состояние взаимной блокировки потоков (deadlock)?

./vector-deadlock -n 2 -l 100 -v -d

    -d
    Этот флаг включает возможность блокировки потоков.
       Когда вы передаете -d программе, каждый другой поток вызывает vector_add ()
       с векторами в другом порядке, например, с двумя потоками, и -d включен,
       Поток 0 вызывает vector_add (v1, v2), а поток 1 вызывает vector_add (v2, v1)
    
Увеличим количество циклов. Взаимная блокировка может иногда возникать 
(в функции vector_add()). (Чем больше сложений, тем вероятнее).
Возникает она только при поподании переключения потоков между мьютексами.

- Теперь меняем число потоков -n. Есть ли такое число потоков, при котором блокировка не возникает?

    
    ./vector-deadlock -n 15 -l 20 -v -d

Взаимная блокировка также может возникать.
Число потоков такое есть, = 1


2.  vector-global-order.c:
2/1 За счет чего программа избегает блокировок? 
2/2 Для чего предусмотрен специальный случай в vector add(), когда исходный и результирующий вектор совпадают?
2/3 Флаги: -t -n 2 -l 100000 -d. Как меняется время в зависимости от числа циклов и числа потоков?
2/4 Что происходит, когда включается ключ -p (при сложении различных векторов и одного и того же)?

2/1. За счет упорядочивания по адресам, благодаря чему сохраняется порядок блокировок и
они вызываются в определенной последовательности.
2/2. для того, чтобы сделать блокировку 1 раз, когда совпадают вектора, иначе
произойдет взаимная блокировка

2/3.

./vector-deadlock -t -n 15 -l 20 -v -d
    
    Time: 0.02 seconds

./vector-deadlock -t -n 15 -l 1000 -v -d
    
    Time: 0.68 seconds

./vector-deadlock -t -n 10 -l 1000 -v -d

    Time: 0.28 seconds

./vector-deadlock -t -n 1 -l 10000 -v -d

    Time: 0.19 seconds

Вывод: при увеличении числа циклов и потоков, время возрастает.

    -t
       Turns on timing and shows how long everything took.
    - t
        Включает хронометраж и показывает, сколько времени все заняло.

2/4.

Возьмем те же параметры для количества циклов и потоков:

./vector-deadlock -t -n 15 -l 20 -v -d

    Time: 0.01 seconds
(а в 2.3 было Time: 0.02 seconds)

./vector-deadlock -t -n 15 -l 1000 -v -d -p

    Time: 0.59 seconds
(а в 2.3 было Time: 0.68 seconds)

Вывод: с флагом -p время уменьшается, т.к:

    -p
       This flag gives each thread a different set of vectors to call add()
       upon, instead of just two vectors. Use this to see how things perform
       when there isn't contention for the same set of vectors.   
       
    - p
        Этот флаг дает каждому потоку отдельный набор векторов для вызова add()
        по факту, а не просто два вектора. Используйте это, чтобы увидеть, как все работает
        когда нет конкуренции за один и тот же набор векторов.   

3. vector-try-wait.c: 
- Нужен ли первый вызов  pthread mutex trylock()?
- Как меняется число повторных попыток, когда растет число потоков?


Вызов pthread_mutex_trylock() для создания порядка блокировки путем блокировки v_dst.
С увеличением числа потоков происходит рост повторных попыток потому, что
переключение между потоками происходит чаще 


4.  vector-avoid-hold-and-wait.c: 
- Сравнить с другими подходами.
- Как меняется производительность в зависимости от наличия флага -p?

Этот метод позволяет избежать взаимной блокировки посредству глобальной блокировки (мьютекса) 
всех потоков.  
 
4.1 
 ./vector-avoid-hold-and-wait -t -n 15 -l 200 -v -d
    
    Time: 0.11 seconds

 ./vector-avoid-hold-and-wait  -t -n 15 -l 10000 -v -d
    
    Time: 4.82 seconds

4.2
 ./vector-avoid-hold-and-wait  -t -n 15 -l 200 -v -d -p
    
    Time: 0.10 seconds

 ./vector-avoid-hold-and-wait  -t -n 15 -l 10000 -v -d -p
    
    Time: 4.57 seconds


5.  vector-nolock.c:
- Сравнить семантику и производительность с другими вариантами при работе 
с двумя одинаковыми векторами и в случае, когда каждый поток работает на своем векторе  -p.

./vector-deadlock -t -n 4 -l 100000 -d 
    
    Time: 4.56 seconds
    
./vector-avoid-hold-and-wait -t -n 4 -l 100000 -d

    Time: 4.68 seconds

./vector-nolock  -t -n 4 -l 100000 -d

    Time: 4.49 seconds

./vector-try-wait  -t -n 4 -l 100000 -d

    Time: 4.56 seconds

________________________________________________________
                        C p
________________________________________________________

./vector-deadlock -t -n 4 -l 100000 -d -p
    
    Time: 4.50 seconds
    
./vector-avoid-hold-and-wait -t -n 4 -l 100000 -d -p

    Time: 4.58 seconds

./vector-nolock  -t -n 4 -l 100000 -d -p
    
    Time: 4.46 seconds

./vector-try-wait  -t -n 4 -l 100000 -d -p

    Time: 4.48 seconds
