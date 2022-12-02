#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int thread_function(void *args)
{
	pid_t thread_pid = getpid();
	pid_t thread_ppid = getppid();

	pid_t thread_id = gettid();

	printf("Thread PID: %u, Thread PPID: %u\n", thread_pid, thread_ppid);
	printf("Thread ID: %u\n", thread_id);

	return 0;
}

int main(void)
{
	void *child_stack = malloc(1024*1024);

	int child_pid = clone(&thread_function, child_stack, CLONE_VM | CLONE_IO | CLONE_FS | CLONE_FILES, NULL);

	printf("Child thread PID: %u\n", child_pid);

	pid_t main_pid = getpid();
	pid_t main_ppid = getppid();

	printf("Main PID: %u, Main PPID: %u\n", main_pid, main_ppid);

	wait(NULL);

	free(child_stack);
	return 0;
}
