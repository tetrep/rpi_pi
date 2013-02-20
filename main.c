#define RPI_PI_SANITIZE_CGI_SHORT_NAMES
#include "rpi_pi_sanitize_cgi.h"

#include <stdio.h>

int main(int argc, char **argv)
{
  char *string1 = "abcdefghijklmnopqrstuvwkyz";
  char *string2 = "tetrep";
  char *string3 = "123456";
  char *string4 = "tetrep'123456'!"; 
  unsigned int num_cstrings = 4;
  int error = 0;

  error = sanitize_cgi(RPI_PI_SANITIZE_CGI_WARN | RPI_PI_SANITIZE_CGI_LIST_WHITE | RPI_PI_SANITIZE_CGI_LIST_BLACK, num_cstrings, string1, string2, string3, string4);

  printf("THE ERROR: %i\n", error);
  printf("STRING1: %s\n", string1);
  printf("STRING2: %s\n", string2);
  printf("STRING3: %s\n", string3);
  printf("STRING4: %s\n", string4);

  return 0;
}
