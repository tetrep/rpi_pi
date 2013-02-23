#include "rpi_pi_execute.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#define RPI_PI_FIFO_PATH "super_dooper_awesome_fifo"

//forks on the given function and redirects its stdout to us
int rpi_pi_forker(void *fp, void *arg)
{
  //pid of our child
  pid_t child_pid = -1;

  //can we open our fifo?
  if(freopen(RPI_PI_FIFO_PATH, "r", stdin) == NULL)
  {
    //fifo might not exist, so make it and try again
    if(mkfifo(RPI_PI_FIFO_PATH, 0660) != 0 || freopen(RPI_PI_FIFO_PATH, "r", stdin) == NULL)
      return -1;
  }

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
      fp(arg);
      break;

    //we made a baby
    default:
      break;
  }

}

int rpi_pi_lpq(char* user, char* printer)
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

int rpi_pi_lpr(char* user, char* printer, void* file)
{
  //char cmd[strlen("su ") + strlen(user) + strlen(" -c 'lpr 

  //return system(cmd);
  //printf("%s, cmd");
  return 0;
}

int rpi_pi_lprm(char* user, char* printer, char* job)
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
