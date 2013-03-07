#define RPI_PI_SANITIZE_CGI_SHORT_NAMES
#include "rpi_pi_sanitize_cgi.h"
#define RPI_PI_EXECUTE_SHORT_NAMES
#include "rpi_pi_execute.h"
#include "rpi_pi_parse_lpq.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
  char string1[strlen("abcdefghijklmnopqrstuvwxyz")+1];
  char string2[strlen("tetrep")+1];
  char string3[strlen("123456")+1];
  char string4[strlen("tetrep'123456'!")+1];
  int error = 0;

  char **test_parse;

  if(argc)
  {}
  else if(argv)
  {}

  strcpy(string1, "abcdefghijklmnopqrstuvwxyz");

  strcpy(string2, "tetrep");

  strcpy(string3, "123456");

  strcpy(string4, "tetrep'123456'!");

  /*
  error = sanitize_cgi(RPI_PI_SANITIZE_CGI_WARN, string1, string2, string3, string4, NULL);
  printf("STRING1: %s\n", string1);
  printf("STRING2: %s\n", string2);
  printf("STRING3: %s\n", string3);
  printf("STRING4: %s\n", string4);
  printf("THE SANITIZE ERROR: %i\n", error);
  printf("=====\n");

  /*
  error = (int) lpq("paul", "vcpltg");
  printf("THE LPQ ERROR: %i\n", error);
  printf("=====\n");

  error = (int) lprm("paul", "vcpltg", "cheese");
  printf("THE LPRM ERROR: %i\n", error);
  printf("=====\n");
  */

  //check forck function and execute lpq
  error = forker(rpi_pi_execute_lpq, "paul", "vcpltg", NULL);
  printf("THE FORKER LPQ ERROR: %i\n", error);
  printf("=====\n");

  //check fork function and execute lprm
  error = forker(rpi_pi_execute_lprm, "paul", "vcpltg", "cheese", NULL);
  printf("THE FORKER LPRM ERROR: %i\n", error);
  printf("=====\n");

  //attempt to parse lpq from stdin
  test_parse = rpi_pi_parse_lpq_job_tok("majumr", "vcplt");
  //did we get something back?
  if(test_parse != NULL)
  {
    error = 0;
    //print out what we got
    while(test_parse[error] != NULL)
    {
      printf("%s\n", test_parse[error]);
      error++;
    }
  }
  //we ran out of memory :(
  else
    printf("PARSE_LPQ FAIL :(\n");

  printf("=====\n");

  return 0;
}
