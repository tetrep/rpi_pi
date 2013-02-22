#define RPI_PI_SANITIZE_CGI_SHORT_NAMES
#include "rpi_pi_sanitize_cgi.h"

#include <stdio.h>

int main(int argc, char **argv)
{
  char string1[27];//abcdefghijklmnopqrstuvwxyz
  char string2[7];//tetrep
  char string3[7];//123456
  char string4[16];//tetrep'123456'!
  unsigned int num_cstrings = 4;
  int error = 0;

  //abcdefghijklmnopqrstuvwxyz
  string1[0] = 'a';
  string1[1] = 'b';
  string1[2] = 'c';
  string1[3] = 'd';
  string1[4] = 'e';
  string1[5] = 'f';
  string1[6] = 'g';
  string1[7] = 'h';
  string1[8] = 'i';
  string1[9] = 'j';
  string1[10] = 'k';
  string1[11] = 'l';
  string1[12] = 'm';
  string1[13] = 'n';
  string1[14] = 'o';
  string1[15] = 'p';
  string1[16] = 'q';
  string1[17] = 'r';
  string1[18] = 's';
  string1[19] = 't';
  string1[20] = 'u';
  string1[21] = 'v';
  string1[22] = 'w';
  string1[23] = 'x';
  string1[24] = 'y';
  string1[25] = 'z';
  string1[26] = '\0';

  //tetrep
  string2[0] = 't';
  string2[1] = 'e';
  string2[2] = 't';
  string2[3] = 'r';
  string2[4] = 'e';
  string2[5] = 'p';
  string2[6] = '\0';

  //123456
  string3[0] = '1';
  string3[1] = '2';
  string3[2] = '3';
  string3[3] = '4';
  string3[4] = '5';
  string3[5] = '6';
  string3[6] = '\0';

  //tetrep'123456'!
  string4[0] = 't';
  string4[1] = 'e';
  string4[2] = 't';
  string4[3] = 'r';
  string4[4] = 'e';
  string4[5] = 'p';
  string4[6] = '\'';
  string4[7] = '1';
  string4[8] = '2';
  string4[9] = '3';
  string4[10] = '4';
  string4[11] = '5';
  string4[12] = '6';
  string4[13] = '\'';
  string4[14] = '!';
  string4[15] = '\0';

  error = sanitize_cgi(RPI_PI_SANITIZE_CGI_WARN | RPI_PI_SANITIZE_CGI_LIST_WHITE | RPI_PI_SANITIZE_CGI_LIST_BLACK, num_cstrings, string1, string2, string3, string4);

  printf("THE ERROR: %i\n", error);
  printf("STRING1: %s\n", string1);
  printf("STRING2: %s\n", string2);
  printf("STRING3: %s\n", string3);
  printf("STRING4: %s\n", string4);

  return 0;
}
