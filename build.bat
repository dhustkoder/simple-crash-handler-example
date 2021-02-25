@echo off

cls

set OUTPUT=crash.exe

set INCLUDE_DIRS=/I./src^
	
set CFLAGS_DEBUG=/DDEBUG=1^
	/DEBUG:FULL^
	/Od^
	/Zi

set CFLAGS_RELEASE=/DNDEBUG /Ox

set CFLAGS=%INCLUDE_DIRS%^
	%CFLAGS_DEBUG%^
	/TC ^
	/cgthreads8 ^
	/MP8^
	/D_CRT_SECURE_NO_WARNINGS ^
	/wd4028 ^
	/wd4214 ^
	/wd4204 ^
	/wd4244 ^
	/W4
	

set LINKER_FLAGS=user32.lib

set C_SRCS=./src/main.c ./src/crash_function.c ./src/crash_handler_win32.c

set CLANG_CL_COMPILER=clang-cl -Wfatal-errors -fstrict-aliasing -Wno-c99-extensions -fsanitize=address
	
set CL_COMPILER=cl

set CCOMPILER=%CL_COMPILER%

@echo on
 %CCOMPILER% %CFLAGS% %CFLAGS_DEBUG% %C_SRCS% /Fe%OUTPUT% /link %LINKER_FLAGS% 
@echo off

set ERROR=%errorLevel%
if NOT %ERROR% == 0 (
	echo "BUILD FAILED"
	GOTO CLEAN
)
:RUN
%OUTPUT%

:CLEAN
del *.obj
