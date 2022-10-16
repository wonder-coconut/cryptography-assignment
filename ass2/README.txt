Critical Values for Chi square taken from:  https://www.omnicalculator.com/statistics/critical-value
Critical Values for KS test taken from:     https://www.real-statistics.com/statistics-tables/kolmogorov-smirnov-table/

OS version: Pop!_OS 22.04 LTS x86_64 
Kernel:     Linux 5.19.0-76051900-generic

1. osrandtest.c tests the rand function given by the OS, (in this case, as it is Linux, the function is the rand() function of C)

Compilation:    gcc osrandtest.c -o osrand -lm
Execution:      ./osrand

2. pyrandtest.py tests the rand function given by python

Compilation/Execution:  python3 pyrandtest.py