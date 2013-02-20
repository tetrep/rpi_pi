#define RPI_PI_SANITIZE_CGI_SHORT_NAMES
#include "rpi_pi_sanitize_cgi.h"

int main(int argc, char **argv)
{
  char *string1 = "abcdefghijklmnopqrstuvwkyz";
  char *string2 = "tetrep";
  char *string3 = "123456";
  char *string4 = "tetrep'123456'!"; 
  unsigned int num_cstrings = 4;

  sanitize_cgi(RPI_PI_SANITIZE_CGI_WARN | RPI_PI_SANITIZE_CGI_FAIL_FAST | RPI_PI_SANITIZE_CGI_LIST_WHITE | RPI_PI_SANITIZE_CGI_LIST_BLACK, num_cstrings, string1, string2, string3, string4);
  return 0;
}
