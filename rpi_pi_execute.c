#include "rpi_pi_execute.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#include <sys/wait.h>

//last one needs to be null
//only 10 supported
#define RPI_PI_EXECUTE_FORKER_ARGS_MAX 11

//forks on the given function and redirects its stdout to us
int rpi_pi_execute_forker(void *(*fp)(), ...)
{
  //our pipe
  int pipefd[2];

  //pid of our child
  pid_t child_pid = -1;

  //our argument list
  va_list arg_list;
  //the arguments we pull out
  void *args[RPI_PI_EXECUTE_FORKER_ARGS_MAX];

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

      va_start(arg_list, fp);
      for(child_pid = 0; child_pid < RPI_PI_EXECUTE_FORKER_ARGS_MAX; child_pid++)
      {
        //grab an argument
        args[child_pid] = va_arg(arg_list, void*);
        if(args[child_pid] == NULL)
          break;
      }
      //we'er done with our arguments
      va_end(arg_list);

      //nasty nasty switch
      switch(child_pid)
      {
        case 0:
          fp();
          break;

        case 1:
          fp(args[0]);
          break;

        case 2:
          fp(args[0], args[1]);
          break;

        case 3:
          fp(args[0], args[1], args[2]);
          break;

        case 4:
          fp(args[0], args[1], args[2], args[3]);
          break;

        case 5:
          fp(args[0], args[1], args[2], args[3], args[4]);
          break;

        case 6:
          fp(args[0], args[1], args[2], args[3], args[4], args[5]);
          break;

        case 7:
          fp(args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
          break;

        case 8:
          fp(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
          break;

        case 9:
          fp(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
          break;

        case 10:
          fp(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9]);
          break;

        default:
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

      //dont read from child, we want to let our caller read
      /*
      while(fread(&sexy_input, 1, 1, stdin) > 0)
        printf("%c", sexy_input);
      */

      //wait for child
      wait(NULL);
  }

  return 0;
}

void *rpi_pi_execute_lpq(char *user, char *printer)
{
  //plus 2 because we need to end the command with ' and \0
  char cmd[strlen("su ") + strlen(user) + strlen(" -c 'lpq -lP") + strlen(printer) + 2];
  //build our command
  cmd[0] = '\0';
  strcat(cmd, "su ");
  strcat(cmd, user);
  strcat(cmd, " -c 'lpq -lP ");
  strcat(cmd, printer);
  strcat(cmd, "'");

  //return system(cmd);
  printf("%s\n", cmd);
  return 0;
}

void *rpi_pi_execute_lpr(char *user, char *printer, void *file)
{
  //char cmd[strlen("su ") + strlen(user) + strlen(" -c 'lpr 

  //return system(cmd);
  //printf("%s, cmd");
  if(user || printer || file)
    return 0;
  else
    return 0;
}

void *rpi_pi_execute_lprm(char *user, char *printer, char *job)
{
  //plus 2 because we need to close the ' and add a \0
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

  //return system(cmd);
  printf("%s\n", cmd);
  return 0;
}
