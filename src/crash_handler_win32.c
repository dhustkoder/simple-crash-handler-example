#include <Windows.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>




LONG crash_handler(EXCEPTION_POINTERS *exception)
{

	unsigned char* backtrace[128];
	USHORT captured ;
	unsigned char* baseAddr = (PVOID) GetModuleHandleA(NULL);
	captured = CaptureStackBackTrace(0, 128, backtrace, NULL);

	FILE* f = fopen("crash_report.txt", "w+");
	fprintf(f, ":: CRASH REPORT ::\n");
	fprintf(f, "ExceptionCode    =>  %X\n", exception->ExceptionRecord->ExceptionCode);
	fprintf(f, "ExceptionFlags   =>  %X\n", exception->ExceptionRecord->ExceptionFlags);
	fprintf(f, "ExceptionAddress =>  %llX\n", (unsigned char*)exception->ExceptionRecord->ExceptionAddress - (baseAddr));

	fprintf(f, ":: BACKTRACE ::\n");
	for (int i = 0; i < captured; ++i) {
		fprintf(f, "%d => %llX\n", i, backtrace[i] - (baseAddr));
	}

	fclose(f);

	exit(-1);
}


void crash_handler_init(void)
{
	SetUnhandledExceptionFilter(crash_handler);
}

