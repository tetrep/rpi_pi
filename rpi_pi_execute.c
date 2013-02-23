#include "rpi_pi_execute.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
