Лабораторная работа № 5
Файлы и файловые системы

1. Используя creat(), write(), fflush(), close(), gettimeofday(), разработать программу, которая
открывает файл,
записывает туда 300 KB,
очищает все записи,
закрывает и
удаляет файл,
а также измеряет и выводит время, затраченное на каждое действие.

Функция gettimeofday() позволяет получить текущее значение системного времени. 
Достоинством этого способа измерения является относительно большая точность измерения.

    открывает файл

creat() - Системный вызов который  либо создает  новый файл,
либо открывает и чистит существующий.

    записывает туда 300 KB,

Следующая строка переписывает 300 байт из buffer в файл task1.
write(f, buffer, mem); Функция write() переписывает mem байт 
из buffer в файл f

    очищает все записи

ftruncate устанавливают длину обычного файла в какое-то количество байт.
 
    закрывает 
    
close - закрывает файл

    удаляет файл

remove - удаляет файл. Если файл был благополучно удален, она возвра­щает 0, а в случае ошибки —1.

затраченное время считаем с помощью gettimeofday()
первым параметром передается структура timeval

    struct timeval {
    long    tv_sec;         /* секунды */
    long    tv_usec;        /* микросекунды */
    };
вторым параметром - 
    
    struct timezone {
    int     tz_minuteswest; /* количество минут коррекции по отношению к Гринвичу */
    int     tz_dsttime;     /* тип сезонной коррекции времени */
    };
но мы не используем коррекцию времени и передаем NULL

.2. Разработать программу, которая замеряет время для 300,000 однобайтовых записей с использованием
a) напрямую POSIX: creat(), write(), close().
b) с использованием библиотеки stdio (напр., fopen(), fwrite(), and fclose()).
Сравнить и объяснить результаты.

a) creat() - Системный вызов который  либо создает  новый файл,
   либо открывает и чистит существующий.
   write(f, buffer, mem); Функция write() переписывает mem байт 
   из buffer в файл f
   close - закрывает файл

b) FILE *fopen (const char *filename, const char *mode);
   
   Аргументы:
   
   filename – указатель на строку содержащую имя (включая путь) открываемого файла.
   mode – указатель на строку содержащую режим доступа к открытому файлу. 
   
   size_t fwrite(const void *буфер, size_t число_байт, size_t объем, FILE *fp);
   fwrite() буфер - это указатель на информацию, записываемую в файл. Длина 
   каждого элемента в байтах определяется в число_байт. Аргумент объем 
   определяет, сколько элементов (каж¬дый длиной число_байт) будет 
   прочитано или записано. Наконец, fp - это файловый указатель на ранее открытый поток. 
   
   Функция fclose() используется для закрытия потока, ранее открытого с помощью fopen()  

Делаем вывод, что useFopen работает быстрее, потому что
метод fwrite использует  буфер, что позволяет снизить количество
дорогостоящих операций обращения к памяти, а write 
напрямую пытается обращаться к памяти 300 000 раз.

.3. Разработать собственную версию (mytail) команды tail.
Формат: mytail -n file
Она читает блок из конца файла, просматривает его с конца до заданного количества 
строк n и печатает эти строки в соответствующем порядке.
Использовать: stat(), lseek(), open(), read(), close(), ...

int stat(char *filename, struct stat *statbuf)
Функция stat() вносит в структуру, на которую указывает statbuf, информацию, 
содержащуюся в файле, связанном с указателем filename. Структура stat определена в 
sys\stat.h.

    Поле                              Значение
                                     
       st_mode              Битовая  маска  для информации о режиме
                            файла.  Бит   S_IFDIR  устанавливается,
                            если  pathname  определяет  директорий;
                            бит   S_IFREG   устанавливается,   если
                            pathname  ссылается  на  обычный  файл.
                            Биты   чтения/записи    устанавливаются
                            пользователем в соответствии с  режимом
                            доступа к файлу. Пользователь выполняет
                            установку битов, используемых для  рас-
                            ширения имени файла.
    
       st_dev               Номер   устройства  диска,  содержащего
                            файл.
         
       st_rdev              Номер   устройства  диска,  содержащего
                            файл.
                            (аналогично st_dev).
                   
       st_nlink             Всегда 1.
                   
       st_size              Размер файла  в байтах.
                   
       st_atime             Время последней модификации файла.
                   
       st_mtime             Время последней модификации файла
                            (аналогично st_atime).
                   
       st_ctime             Время последней модификации файла
                            (аналогично st_atime и st_mtime).

При успешном заполнении структуры stat возвращается 0. В случае неудачи возвращается —1, 
а errno устанавливается в ENOENT.

Алгоритм:
получаем количество строк
октрываем файл
с помощью стат в структуру получаем информацию о файле
выделяем память на сохранение строк (стек на размер всего файла, +1 из-за \0)
заводим счетчик на количество строк 
if (lseek(file_input, -offset, SEEK_END) != -1L) - перемещаем
указатель позиции чтения в конец - смещение, если не получилось - вернет -1
считаем количество строк, но если это пустая строка, то мы не считаем ее,
пока не достигнуто нужное количество, потом выводим строки

tests:

![logo](https://i.ibb.co/v3xFgK7/2020-06-04-16-51-07.png)
![logo](https://i.ibb.co/1GH15mX/2020-06-04-16-53-21.png)

.4. Разработать собственную версию (mystat) команды stat, которая просто осуществляет 
системный вызов stat(), выводит размер, число задействованных блоков, число ссылок 
и т.д. Отследить, как меняется число ссылок, когда изменяется содержимое директории.

Алгоритм:
просто используем поля stat - .st_size (размер), .st_nlink (ссылки), .st_blocks(блоки)

При изменении директории количество ссылок не меняется, но если принудительно создать 
на него ссылку (ln file new_file), то количество ссылок изменится.
 ln создает жесткую ссылку. Жесткая ссылка - тот же номер индекса, что и файл, на который она ссылается
 символическая ссылка - Главное ее отличие от жестких ссылок в том, что при удалении целевого файла 
 ссылка останется, но она будет указывать в никуда, поскольку файла на самом деле больше нет.

Я создала с помощью ln жесткую ссылку 

    ln data.txt data3
    
Таким образом, число ссылок стало = 2.

tests:

![logo](https://i.ibb.co/pRHrsD2/2020-06-04-16-59-44.png)

добавляем текст в файл
и удаляем файл, который ссылался на тестовый

![logo](https://i.ibb.co/8xc3QQ6/2020-06-04-17-01-14.png)

.5. Разработать собственную версию (myls) команды ls, которая выводит список файлов в 
заданной директории. С ключом -l она выводит информацию о каждом файле, включая 
собственника, группу, разрешения и т.д., получаемые из системного вызова stat().
Формат: myls -l directory (или текущую директорию, если параметр не задан)
Использовать: stat(), opendir(), readdir(), getcwd()
    
    Директория сама по себе представляет файл состоящий из специальных записей dirent, 
    которые содержат данные о файлах в директории:
    
    struct dirent {
      ino_t          d_ino;       /* inode number */
      off_t          d_off;       /* offset to the next dirent */
      unsigned short d_reclen;    /* length of this record */
      unsigned char  d_type;      /* type of file; not supported
                                     by all file system types */
      char           d_name[256]; /* filename */
    };

    Для открытия/закрытия директорий существует две функции:
    
    DIR *opendir(const char *name);
    int closedir(DIR *dirp);
    
Функция opendir() открывает директорию для чтения с именем name и возвращает 
указатель на directory stream (иногда сложно перевести со смыслом, директорный 
поток или поток директории ?), при ошибке возвращает NULL и соответствующим образом 
устанавливает код ошибки errno. Функция closedir() без комментариев. 

     d_type принимает значения
    
          DT_BLK      This is a block device.

          DT_CHR      This is a character device.

          DT_DIR      This is a directory.

          DT_FIFO     This is a named pipe (FIFO).

          DT_LNK      This is a symbolic link.

          DT_REG      This is a regular file.

          DT_SOCK     This is a UNIX domain socket.

          DT_UNKNOWN  The file type could not be determined.
          
int sprintf(char *buf, const char *format, arg-list)
Описание: 

    Функция sprintf() идентична printf(), за исключением того, что вывод производится в массив, указанный аргументом buf.
    
    Возвращаемая величина равна количеству символов, действительно занесенных в массив.
    
tests:

../lab1/
![logo](https://i.ibb.co/FYT5V7t/2020-06-04-17-14-26.png)

../lab5/
![logo](https://i.ibb.co/tJ7z43m/2020-06-04-17-19-14.png)
