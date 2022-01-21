@echo off

:::::: Constants ::::::
setlocal EnableDelayedExpansion

:: Directories
set BUILD_DIR=build\
set OBJ_DIR=%BUILD_DIR%obj\
set ASM_DIR=%BUILD_DIR%asm\
set SRC_DIR=src\
set TEST_DIR=test\

:: Files
set BINARY=%BUILD_DIR%bad.exe
set SRC=
set OBJ=

:: Compilation flags
set COMP=clang++ -std=c++17 -pipe
:: Don't replace INCLUDE_DIR by INCLUDE. INCLUDE can be a global path variable
set INCLUDE_DIR=-I%SRC_DIR% -I%TEST_DIR%
set MACRO=-DNDEBUG
::  -ferror-limit=0
set WARNING=-W -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -Wno-uninitialized -Wfatal-errors
set OPTI=-O3 -march=native -mno-vaes
set ASM=-fverbose-asm -masm=intel

:: Rules
if "%1"=="" (
    call :compile
    exit /B 0
) else if "%1"=="asm" (
    call :asm
    exit /B 0
) else if "%1"=="run" (
    if not exist %BINARY% (
        call :compile
    )
    
    if exist %BINARY% (
        %BINARY%
    )
    exit /B 0
) else if "%1"=="clean" (
    rmdir /Q /S %BUILD_DIR% 2> nul
    echo %BUILD_DIR% deleted
    exit /B 0
) else (
    echo Undefined rule
    exit /B 0
)


:: Find the C++ sources and put them in SRC
:find_src
    for /R %SRC_DIR% %%f in (*.cpp) do (
        set file=%%f
        set "SRC=!SRC!!file! "
    )
    for /R %TEST_DIR% %%f in (*.cpp) do (
        set file=%%f
        set "SRC=!SRC!!file! "
    )
    exit /B 0


:: Asm output
:asm
    setlocal EnableDelayedExpansion
    call :find_src

    :: Create the build and objects directories if they do not exist
    mkdir %BUILD_DIR% 2> nul
    mkdir %ASM_DIR% 2> nul

    echo Compiling to asm...
    for %%i in (!SRC!) do (
        set src_file=%%~nxi
        set asm_file=!src_file:.cpp=.asm!
        set asm_file=%~dp0%!ASM_DIR!!asm_file!
        
        %COMP% %INCLUDE_DIR% %MACRO% %WARNING% %OPTI% %ASM% -S %%i -o !asm_file!
    )
    echo Done
    exit /B 0


:: Compile into a binary
:compile
    setlocal EnableDelayedExpansion
    call :find_src

    :: Create the build and objects directories if they do not exist
    mkdir %BUILD_DIR% 2> nul
    mkdir %OBJ_DIR% 2> nul

    echo Compiling to %BINARY%...
    echo(
    set "startTime=%time: =0%"

    :: Isolate the file and its extension from the absolute path to make its .o file path
    for %%i in (!SRC!) do (
        set src_file=%%~nxi
        set obj_file=!src_file:.cpp=.o!
        set obj_file=%~dp0%!OBJ_DIR!!obj_file!
        set "OBJ=!OBJ!!obj_file! "
        
        %COMP% %INCLUDE_DIR% %MACRO% %WARNING% %OPTI% -c %%i -o !obj_file!
    )

    %COMP% %WARNING% %OPTI% %LIB% !OBJ! -o %BINARY%

    :: https://stackoverflow.com/a/9935540
    set "endTime=%time: =0%"
    set "end=!endTime:%time:~8,1%=%%100)*100+1!" & set "start=!startTime:%time:~8,1%=%%100)*100+1!"
    set /A "elap=((((10!end:%time:~2,1%=%%100)*60+1!%%100)-((((10!start:%time:~2,1%=%%100)*60+1!%%100), elap-=(elap>>31)*24*60*60*100"
    set /A "cc=elap%%100+100,elap/=100,ss=elap%%60+100,elap/=60,mm=elap%%60+100,hh=elap/60+100"

    echo Done
    echo Compilation time: %hh:~1%h%time:~2,1%%mm:~1%min%time:~2,1%%ss:~1%%time:~8,1%%cc:~1%s
    exit /B 0