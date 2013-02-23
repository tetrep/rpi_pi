#define RPI_PI_SANITIZE_CGI_SHORT_NAMES
#include "rpi_pi_sanitize_cgi.h"
#define RPI_PI_EXECUTE_SHORT_NAMES
#include "rpi_pi_execute.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
  char string1[strlen("abcdefghijklmnopqrstuvwxyz")+1];
  char string2[strlen("tetrep")+1];
  char string3[strlen("123456")+1];
  char string4[strlen("tetrep'123456'!")+1];
  int error = 0;

  strcpy(string1, "abcdefghijklmnopqrstuvwxyz");

  strcpy(string2, "tetrep");

  strcpy(string3, "123456");

  strcpy(string4, "tetrep'123456'!");

  error = sanitize_cgi(RPI_PI_SANITIZE_CGI_WARN, string1, string2, string3, string4, NULL);

  printf("STRING1: %s\n", string1);
  printf("STRING2: %s\n", string2);
  printf("STRING3: %s\n", string3);
  printf("STRING4: %s\n", string4);
  printf("THE SANITIZE ERROR: %i\n", error);
  printf("=====\n");

  error = lpq("paul", "vcpltg");

  printf("THE LPQ ERROR: %i\n", error);
  printf("=====\n");

  error = lprm("paul", "vcpltg", "cheese");

  printf("THE LPRM ERROR: %i\n", error);
  printf("=====\n");

  return 0;
}
