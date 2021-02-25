#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <execinfo.h>




void crash_handler(int sig, siginfo_t * info, void * ucontext)
{
	static void* backtrace_table[128];
	size_t table_size = 0;

	ucontext_t *uc = (ucontext_t *)ucontext;

	FILE* f = fopen("crash_report.txt", "w+");

	fprintf(f, "CRASH SIGNAL: %d\n", sig);

	table_size = backtrace(backtrace_table, 128);
	char** hr_table = backtrace_symbols(backtrace_table, table_size);

	fprintf(f, "SINGAL NUMBER: %d\n", info->si_signo);
	fprintf(f, "ERRNO: %d\n", info->si_errno);
	fprintf(f, "SIGNAL CODE: %d\n", info->si_code);
	
	fprintf(f, "MEMORY VIOLATION ADDRESS => %p\n", info->si_addr);
	fprintf(f, "INSTRUCTION ADDRESS => 0x%.16llX\n", uc->uc_mcontext->__ss.__rip);
	
	fprintf(f, "::: CALL STACK :::\n");
	for (int i = 0; i < table_size; ++i) {
		fprintf(f, "%d = %s\n", i, hr_table[i]);
	}

	free(hr_table);
	fclose(f);

	exit(-1);
}


void crash_handler_init(void)
{
	struct sigaction sigact;
	memset(&sigact, 0x00, sizeof(sigact));
	sigact.sa_sigaction = crash_handler;
	sigact.sa_flags = SA_SIGINFO;

	sigaction(SIGHUP, &sigact, NULL);
	sigaction(SIGTERM, &sigact, NULL);
	sigaction(SIGABRT, &sigact, NULL); 
	sigaction(SIGQUIT, &sigact, NULL); 
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGTRAP, &sigact, NULL);
	sigaction(SIGILL, &sigact, NULL); 
	sigaction(SIGFPE, &sigact, NULL); 
	sigaction(SIGSEGV, &sigact, NULL); 
}

