Лабораторная работа № 2
Управление процессами

task_1 и task_4:
1)
fork() - системный вызов, который создает новый процесс
При вызове fork() порождается новый процесс (процесс-потомок), который почти идентичен порождающему процессу-родителю. 
Процесс-потомок наследует следующие признаки родителя:

    сегменты кода, данных и стека программы;
    таблицу файлов, в которой находятся состояния флагов дескрипторов файла, указывающие, читается ли файл или пишется. Кроме того, в таблице файлов содержится текущая позиция указателя записи-чтения;
    рабочий и корневой каталоги;
    реальный и эффективный номер пользователя и номер группы;
    приоритеты процесса (администратор может изменить их через nice);
    контрольный терминал;
    маску сигналов;
    ограничения по ресурсам;
    сведения о среде выполнения;
    разделяемые сегменты памяти.

Потомок не наследует от родителя следующих признаков:

    идентификатора процесса (PID, PPID);
    израсходованного времени ЦП (оно обнуляется);
    сигналов процесса-родителя, требующих ответа;
    блокированных файлов (record locking).

При вызове fork() возникают два полностью идентичных процесса. 
Весь код после fork() выполняется дважды, как в процессе-потомке, так и в процессе-родителе.

Процесс-потомок и процесс-родитель получают разные коды возврата после вызова fork(). Процесс-родитель получает 
идентификатор потомка. Если это значение будет отрицательным, следовательно при порождении процесса произошла 
ошибка. Процесс-потомок получает в качестве кода возврата значение 0, если вызов fork() оказался успешным. 
 
![logo](https://i.ibb.co/hm7hHPg/2020-04-09-17-01-09.png)

Здесь мы видим, что первым выполняется процесс-родитель, вторым - процесс-потомок.

4)Но, есть такая функия, как wait().  

![logo](https://i.ibb.co/cD6XpyL/2020-04-09-17-11-16.png)
 pid_t wait(int *status)
 pid_t waitpid(pid_t pid, int *status, int options);
Функция wait приостанавливает выполнение текущего процесса до тех пор, пока дочерний процесс не завершится, или до 
появления сигнала, который либо завершает текущий процесс, либо требует вызвать функцию-обработчик. 

Функция waitpid приостанавливает выполнение текущего процесса до тех пор, пока дочерний процесс, указанный в параметре 
pid, не завершит выполнение, или пока не появится сигнал, который либо завершает текущий процесс либо требует вызвать 
функцию-обработчик.
Параметр pid может принимать несколько значений:

< -1
    означает, что нужно ждать любого дочернего процесса, идентификатор группы процессов которого равен абсолютному значению pid. 
-1
    означает ожидание любого дочернего процесса; функция wait ведет себя точно так же. 
0
    означает ожидание любого дочернего процесса, идентификатор группы процессов которого равен идентификатору текущего процесса. 
> 0
    означает ожидание дочернего процесса, чей идентификатор равен pid. 

Возвращает идентификатор дочернего процесса, который завершил выполнение, или ноль, если ни один дочерний процесс 
пока еще недоступен, или -1 в случае ошибки 

Значение options создается путем битовой операции ИЛИ над следующими константами:

       WNOHANG
              означает вернуть управление немедленно, если ни один дочерний процесс  не  завершил
              выполнение.

       WUNTRACED
              означает  возвращать  управление также для остановленных дочерних процессов, о чьем
              статусе еще не было сообщено.

       Если status не равен NULL, то функции wait и waitpid  сохраняют  информацию  о  статусе  в
       переменной, на которую указывает status.
       
       
 waitpid():
![logo](https://i.ibb.co/p2WYq9r/2020-04-09-17-34-39.png)      
       
2 task: 
для выполнения задачи пользуемся двумя функциями:
kill (p_pid, sign) - стандартаня функция linux, pid - Указать список идентификаторов процессов, которым команда 
kill должна послать сигнал. Каждый аргумент pid должен быть номером процесса либо его именем.
SIGCONT - сигнал, посылаемый для возобновления выполнения процесса, ранее остановленного 

То есть, сначала выполянется родитель, signal передает управление в sig_handler, pause останавливает родителя,
Выполняется процесс-потомок, печатает hello, kill передает сигнал функции, что ее работа должна продолжаться,
печатается goodbye, работа завершается. 

![logo](https://i.ibb.co/rsV87cx/2020-04-09-17-39-53.png)

3 task:
/*Функция exec() (execute) загружает и запускает другую программу.
   
   *  Суффиксы l, v, p, e в именах функций определяют формат и объем аргументов,
   а также каталоги, в которых нужно искать загружаемую программу:

    l (список). Аргументы командной строки передаются в форме списка arg0,
   arg1.... argn, NULL. Эту форму используют, если количество аргументов
   известно; v (vector). Аргументы командной строки передаются в форме вектора
   argv[]. Отдельные аргументы адресуются через argv [0], argv [1]... argv [n].
   Последний аргумент (argv [n]) должен быть указателем NULL; p (path).
   передаем путь исполняемой программы, аргументами говорим, что  нужно исполнить

   */
ls - показывается содержимое каталога
-l                         использовать широкий формат

![logo](https://i.ibb.co/qF4Q8bW/2020-04-09-17-42-34.png)

8.
Функции pipe передается указатель на массив из двух целочисленных файловых дескрипторов. Она заполняет массив двумя 
новыми файловыми дескрипторами и возвращает 0. В случае неудачи она вернет -1.
Данные обрабатываются по алгоритму "первым пришел, первым обслужен"

Как это работает:
есть труба - pipe
есть массив дескрипторов, которые, по своей сути, представляет собой понятие, с какой стороны трубы работаем
0 - начало, 1 - конец
в первом порожденном процессе мы закрываем первый вход трубы, через открытый вход "наливаем" данные
закрываем вход
во втором порожденном процессе нам остается просто считать в buf "воду" из трубы 
и вывести
