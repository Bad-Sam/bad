@echo off

:::::: Constants ::::::
setlocal EnableDelayedExpansion

:: Directories
set "BUILD_DIR=build\"
set "OBJ_DIR=%BUILD_DIR%obj\"
set "ASM_DIR=%BUILD_DIR%asm\"
set "SRC_DIR=src\"
set "TEST_DIR=test\"

:: Files
set "BINARY=%BUILD_DIR%bad.exe"
set "SRC="
set "OBJ="
set "SANDBOX_MAIN=sandbox.c"

:: Compilation
set "COMP=clang"
set "INCLUDE_DIR=-I%SRC_DIR%"
set "MACRO=-DNDEBUG"
set "WARNING=-W -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -Wno-uninitialized"
set "OPTI=-O3 -march=native -mno-vaes"
set "ASM=-fverbose-asm -masm=intel"

:: Rules
if "%1"=="" (
    set "SRC=%SANDBOX_MAIN% "
    call :find_src
    call :compile
    exit /B 0
) else if "%1"=="asm" (
    call :find_src
    call :asm
    exit /B 0
) else if "%1"=="test" (
    set "INCLUDE_DIR=%INCLUDE_DIR% -I%TEST_DIR%"
    call :find_src
    call :find_test
    call :compile
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


:find_src
    for /R %SRC_DIR% %%f in (*.cpp) do (
        set "file=%%f"
        set "SRC=!SRC!!file! "
    )
    exit /B 0


:find_test
    for /R %TEST_DIR% %%f in (*.cpp) do (
        set "file=%%f"
        set "SRC=!SRC!!file! "
    )
    exit /B 0


:asm
    setlocal EnableDelayedExpansion

    :: Create the build and objects directories if they do not exist
    mkdir %BUILD_DIR% 2> nul
    mkdir %ASM_DIR% 2> nul

    echo Compiling to asm...
    for %%i in (!SRC!) do (
        set "src_file=%%~nxi"
        set "asm_file=!src_file:.cpp=.asm!"
        set "asm_file=%~dp0%!ASM_DIR!!asm_file!"
        
        %COMP% %INCLUDE_DIR% %MACRO% %WARNING% %OPTI% %ASM% -S %%i -o !asm_file!
    )
    echo Done
    exit /B 0


:compile
    setlocal EnableDelayedExpansion

    :: Create the build and objects directories if they do not exist
    mkdir %BUILD_DIR% 2> nul
    ::mkdir %OBJ_DIR% 2> nul

    echo Compiling to %BINARY%...
    echo(
    set "startTime=%time: =0%"

    :: Isolate the file and its extension from the absolute path to make its .o file path
    ::for %%i in (!SRC!) do (
    ::    set src_file=%%~nxi
    ::    set obj_file=!src_file:.cpp=.o!
    ::    set obj_file=%~dp0%!OBJ_DIR!!obj_file!
    ::    set "OBJ=!OBJ!!obj_file! "
    ::    
    ::    %COMP% %INCLUDE_DIR% %MACRO% %WARNING% %OPTI% -c %%i -o !obj_file!
    ::)

    %COMP% %INCLUDE_DIR% %MACRO% %WARNING% %OPTI% %LIB% !SRC! -o %BINARY%

    :: https://stackoverflow.com/a/9935540
    set "endTime=%time: =0%"
    set "end=!endTime:%time:~8,1%=%%100)*100+1!" & set "start=!startTime:%time:~8,1%=%%100)*100+1!"
    set /A "elap=((((10!end:%time:~2,1%=%%100)*60+1!%%100)-((((10!start:%time:~2,1%=%%100)*60+1!%%100), elap-=(elap>>31)*24*60*60*100"
    set /A "cc=elap%%100+100,elap/=100,ss=elap%%60+100,elap/=60,mm=elap%%60+100,hh=elap/60+100"

    echo Done
    echo Compilation time: %hh:~1%h%time:~2,1%%mm:~1%min%time:~2,1%%ss:~1%%time:~8,1%%cc:~1%s
    exit /B 0