#include "rpi_pi_execute.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//last one needs to be null
//only 10 supported
#define RPI_PI_EXECUTE_FORKER_ARGS_MAX 11

//forks on the given function and redirects its stdout to us
//@TODO finally verified my suspicions, this only works on sheer stack frame luck, need to fix
int rpi_pi_execute_forker(void *(*fp)(va_list*), ...)
{
  
  //our pipe
  int pipefd[2];

  //pid of our child
  pid_t child_pid = -1;

  //our argument list
  va_list args;

  //pipe it!
  if(pipe(pipefd) == -1)
    return -1;

  //fork it!
  child_pid = fork();

  //did it fork?
  switch(child_pid)
  {
    //we failed
    case -1:
      return -1;
      break;

    //we are a baby
    case 0:
      //close read end, we want to write
      close(pipefd[0]);
      //redirect stdout
      fclose(stdout);
      stdout = fdopen(pipefd[1], "w");

      fclose(stdout);
      close(pipefd[1]);
      exit(0);
      }

      fclose(stdout);
      close(pipefd[1]);
      exit(0);
      break;

    //we made a baby
    default:
      //we don't want to write
      close(pipefd[1]);

      fclose(stdin);
      stdin = fdopen(pipefd[0], "r");

      //wait for child
      wait(NULL);

      close(pipefd[0]);
  }
  */
  return 0;
}

//@TODO optimize string generation
void* rpi_pi_execute_lpq(char* user, char* printer)
{
  //plus 2 because we needt to close the ' and null terminate
  char cmd[strlen("su ") + strlen(user) + strlen(" -c 'lpq -lP") + strlen(printer) + 2];
  //build our command
  cmd[0] = '\0';
  strcat(cmd, "su ");
  strcat(cmd, user);
  strcat(cmd, " -c 'lpq -lP ");
  strcat(cmd, printer);
  strcat(cmd, "'");

  system(cmd);

  return NULL;
}

//@TODO optimize string generation
void* rpi_pi_execute_lpr(char* user, char* printer, void* file)
{
  char* filename = "test.postyscripts";
  //plus 2 because we needt to close the ' and null terminate
  char cmd[strlen("su ") + strlen(user) + strlen(" -c 'lpr -P ") + strlen(printer) + strlen(filename) + 2];
  int fd, x;

  //save postscript file for later printing/troubleshooting
  fd = creat(filename, 0660);
  if(fd != -1)
  {
    x = 0;
    while(((char *) file)[x] != '\0')
    {
      write(fd, &((char *) file)[x], 1);
      x++;
    }
  }

  //we're done with the file
  close(fd);

  //build our command
  cmd[0] = '\0';
  strcat(cmd, "su ");
  strcat(cmd, user);
  strcat(cmd, " -c 'lpr -P ");
  strcat(cmd, printer);
  strcat(cmd, filename);
  strcat(cmd, "'");

  system(cmd);

  return NULL;
}

//@TODO optimize string generation
void* rpi_pi_execute_lprm(char* user, char* printer, char* job)
{
  //plus 2 because we needt to close the ' and null terminate
  char cmd[strlen("su ") + strlen(user) + strlen(" -c 'lprm -P ") + strlen(printer) + strlen(job) + 2];

  //build our command
  cmd[0] = '\0';
  strcat(cmd, "su ");
  strcat(cmd, user);
  strcat(cmd, " -c 'lprm -P ");
  strcat(cmd, printer);
  strcat(cmd, " ");
  strcat(cmd, job);
  strcat(cmd, "'");

  system(cmd);

  return NULL;
}
