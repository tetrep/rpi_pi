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

//forks on the given function and redirects its stdout to us
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

      if(stdout == NULL)
        exit(-1);

      //set up va_list
      va_start(args, fp);

      //call the function
      fp(&args);

      //flush and close our end of the pipe
      fclose(stdout);

      va_end(args);

      //we don't want the child to do anything else
      exit(0);

      break;

    //we made a baby
    default:
      //we don't want to write
      close(pipefd[1]);

      //redirect pipe to stdin
      fclose(stdin);
      stdin = fdopen(pipefd[0], "r");

      //wait for child
      wait(NULL);

      //close our end of the pipe
      close(pipefd[0]);
  }

  return 0;
}

//@TODO optimize string generation
void *rpi_pi_execute_lpq(va_list *args)
{
  //get user name
  char *user = va_arg(*args, char*);
  //get printer name
  char *printer = va_arg(*args, char*);

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
void* rpi_pi_execute_lpr(va_list *args)
{
  //get user name
  char *user = va_arg(*args, char*);
  //get printer name
  char *printer = va_arg(*args, char*);
  //get file name
  char *file = va_arg(*args, char*);

  //temp file name
  char *filename = "test.postyscripts";

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
void *rpi_pi_execute_lprm(va_list *args)
{
  //get user name
  char *user = va_arg(*args, char*);
  //get printer name
  char *printer = va_arg(*args, char*);
  //get job id
  char *job = va_arg(*args, char*);

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
