#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

FILE *fptr;
int stat;
pid_t fork_val = -1;

void tle_handler() {
  kill(fork_val, SIGKILL);
  fprintf(fptr, "TIMEOUT\n");
  exit(127);
}

int main(int argc, char *argv[]) {
  fptr = fopen("confine_result.txt", "w");
  if (fptr == NULL) {
    printf("Error creating file!");
    exit(1);
  }

  int result_code = 0;
  char *result_status = "NORMAL";

  if(argc == 1) {
	fprintf(stderr, "Usage: %s /path/to/program args...\n", argv[0]);
	exit(1);
  }

  fork_val = fork();

  if (fork_val == 0) 
  { // Child thread

    // Set memory and file size limit
    struct rlimit memory_limit;
    struct rlimit file_limit;

    memory_limit.rlim_cur = 64*1024*1024;
    memory_limit.rlim_max = 64*1024*1024;

    file_limit.rlim_cur = 4*1024*1024;
    file_limit.rlim_max = 4*1024*1024;

    setrlimit(RLIMIT_AS, &memory_limit);
    setrlimit(RLIMIT_FSIZE, &file_limit);

    char *newargv[argc-1];
    char *newenviron[] = {NULL};

    for (int i = 0; i < argc; i++) 
    {
      newargv[i] = argv[i+1];
    }

    if (execve(argv[1], newargv, newenviron) == -1) 
    {
      exit(1);
    }
    // perror("execve");
    // exit(EXIT_FAILURE);
  } 

  else if (fork_val < 0) 
  { // Failed to create child thread
    exit(-1);
  } 

  else 
  { // Parent thread
    for (int i = 1; i < argc; i++) 
    {
      fprintf(fptr, "%s ", argv[i]);
    }
    fprintf(fptr, "\n");

    // Set time limit
    struct itimerval it_val;
    int which = ITIMER_REAL;

    struct sigaction sig_act;
    sigemptyset(&sig_act.sa_mask);
    sig_act.sa_flags = 0;
    sig_act.sa_handler = &tle_handler;
    sigaction(SIGALRM, &sig_act, NULL);

    alarm(60);

    waitpid(fork_val, &stat, 0);

    if (WTERMSIG(stat))
      {
        result_code = 128;
        result_status = "TERMINATED";
        fprintf(fptr, "%s\n", result_status);
        return result_code;
      }
      else
      {
        result_code = 0;
        result_status = "NORMAL";
        fprintf(fptr, "%s\n", result_status);
        return result_code;
      }
    }
  return result_code;
}
