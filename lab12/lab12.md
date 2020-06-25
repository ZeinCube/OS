Лабораторная работа № 10
Проанализируйте cache.c  и с ее использованием исследуйте параметры 
кэша на вашем компьютере. Для этого 
1. постройте графики времени доступа как функции длины массива, шага 
выборки и размера буфера. 

![logo](https://i.ibb.co/xsx1BmR/2020-06-18-21-11-50.png)

2. на их основе сформулируйте обоснованные гипотезы о  размере кэша, 
размере блока, наличию кэша более высокого уровня.

Как видно из графика, стремительный рост access time происходит примерно на 2^21,
что примерно = 2 мб 
![logo](https://i.ibb.co/gDVLY1R/2020-06-18-21-43-53.png)
 
 
На размере блока выше 64 байт происходит увеличение access time, что может 
быть связано с тем, что физический размер блока -- 64 байта. 
 
Посередине между 2^19 и 2^20 заметны небольшие изменения графика, что около 1 Мб
 
3. сравните свои оценки с реальными значениями, полученными через 
вызов системных функций или из технического описания вашего компьютера.

   
    lscpu - команда, выводящая информацию об архитектуре процессора.
    
    [botinok@farshMac lab12]$ lscpu
    Архитектура:                     x86_64
    CPU op-mode(s):                  32-bit, 64-bit
    Порядок байт:                    Little Endian
    Address sizes:                   39 bits physical, 48 bits virtual
    CPU(s):                          12
    On-line CPU(s) list:             0-11
    Thread(s) per core:              2
    Ядер на сокет:                   6
    Сокетов:                         1
    NUMA node(s):                    1
    ID прроизводителя:               GenuineIntel
    Семейство ЦПУ:                   6
    Модель:                          158
    Имя модели:                      Intel(R) Core(TM) i7-8750H CPU @ 2.20GHz
    Степпинг:                        10
    CPU MHz:                         899.513
    CPU max MHz:                     4100,0000
    CPU min MHz:                     800,0000
    BogoMIPS:                        4401.32
    Виртуализация:                   VT-x
    L1d cache:                       192 KiB
    L1i cache:                       192 KiB
    L2 cache:                        1,5 MiB
    L3 cache:                        9 MiB
    NUMA node0 CPU(s):               0-11
    Vulnerability Itlb multihit:     KVM: Mitigation: Split huge pages
    Vulnerability L1tf:              Mitigation; PTE Inversion; VMX conditional cache flushes, SMT vulnerable
    Vulnerability Mds:               Mitigation; Clear CPU buffers; SMT vulnerable
    Vulnerability Meltdown:          Mitigation; PTI
    Vulnerability Spec store bypass: Mitigation; Speculative Store Bypass disabled via prctl and seccomp
    Vulnerability Spectre v1:        Mitigation; usercopy/swapgs barriers and __user pointer sanitization
    Vulnerability Spectre v2:        Mitigation; Full generic retpoline, IBPB conditional, IBRS_FW, STIBP conditional, RSB filling
    Vulnerability Tsx async abort:   Not affected
    Флаги:                           fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid a
                                     perfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single pt
                                     i ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid ept_ad fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm ida arat pln pts hwp hwp_notify 
                                     hwp_act_window hwp_epp md_clear flush_l1d

cat /proc/cpuinfo - команда, выводящая информацию о процессоре.
воспользуемся ею, чтобы узнать реальный размер блока

    cache_alignment : 64

На основании графика, мы угадали:
размер кэша
размер блока
наличие кэша более высокого уровня - как оказалось, мы угадали размер кжш второго уровня