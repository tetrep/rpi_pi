#include "rpi_pi_execute.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int rpi_pi_lpq(char* user, char* printer)
{
    //plus 2 because we need to end the command with ' and \0
    char cmd[strlen("su ") + strlen(user) + strlen(" -c 'lpq -lP") + strlen(printer) + 2];
    //build our command
    strcat(cmd, "su ");
    strcat(cmd, user);
    strcat(cmd, " -c 'lpq -lP");
    strcat(cmd, printer);
    strcat(cmd, "'");

    return system(cmd);
}

int rpi_pi_lpr(char* user, char* printer, void* file)
{
  //char cmd[strlen("su ") + strlen(user) + strlen(" -c 'lpr 
  //return system(cmd);
  return 0;
}

int rpi_pi_lprm(char* user, char* printer, char* job)
{
  //char cmd[strlen("su ") + strlen(user) + srlen(" -c 'lprm -P
  //return system(cmd);
  return 0;
}
