@echo off

gcc -o xgrep.exe -O3 -static-libgcc -static -lpthread^
    args.c^
    main.c^
    result.c
