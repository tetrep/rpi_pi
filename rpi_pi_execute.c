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
#include <errno.h>

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

      //no debugging!
      fclose(stderr);

      //redirect stdout
      fclose(stdout);
      stdout = fdopen(pipefd[1], "w");

      //did the redirection work?
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
  }

  return 0;
}

void rpi_pi_execute_su_c(char *user, char *cmd)
{
  //become user and execute cmd
  execlp("su", user, "-c", cmd, NULL);

  //we'll only get here if exec failed
  printf("error!\n  user: %s\n  cmd: %s\n  errno: %i\n", user, cmd, errno);
}

//@TODO optimize string generation
void *rpi_pi_execute_lpq(va_list *args)
{
  //get user name
  char *user = va_arg(*args, char*);
  //get printer name
  char *printer = va_arg(*args, char*);

  //allocate lpq command, + 1 for \0
  char cmd[strlen("lpq -lP ") + strlen(printer) + 1];

  //make it an empty cstring
  cmd[0] = '\0';
  //build cmd
  strcat(cmd, "lpq -lP ");
  strcat(cmd, printer);
  
  //run cmd as user
  rpi_pi_execute_su_c(user, cmd);

  return NULL;
}

//@TODO optimize string generation, 1 write or n writes?
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
  //allocate memory for command, +1 for space and +1 for \0
  char cmd[strlen("lpr -P ") + strlen(printer) + 1 + strlen(filename) + 1];

  //save postscript file for later printing/troubleshooting
  int x, fd = creat(filename, 0660);
  if(fd != -1)
  {
    x = 0;
    //keep going until we reach the end
    while(file[x] != '\0')
    {
      write(fd, &file[x], 1);
      x++;
    }
  }

  //we're done with the file
  close(fd);

  //make lprc an empty cstring
  cmd[0] = '\0';
  strcat(cmd, "lpr -P ");
  strcat(cmd, printer);
  strcat(cmd, " ");
  strcat(cmd, filename);
  
  //run cmd as user
  rpi_pi_execute_su_c(user, cmd);

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

  //allocate memory for command, +1 for space +1 for \0
  char cmd[strlen("lprm -P ") + strlen(printer) + 1 + strlen(job) + 1];

  //make it an empty cstring
  cmd[0] = '\0';
  strcat(cmd, "lprm -P ");
  strcat(cmd, printer);
  strcat(cmd, " ");
  strcat(cmd, job);

  //run cmd as user
  rpi_pi_execute_su_c(user, cmd);

  return NULL;
}
