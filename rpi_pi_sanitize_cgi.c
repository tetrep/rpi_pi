#include "rpi_pi_sanitize_cgi.h"

#include <stdio.h>
#include <stdarg.h>

unsigned int rpi_pi_sanitize_cgi(unsigned int flags, unsigned int num_cstrings, ...)
{
  //all our cstrings
  va_list args = NULL;
  //our white/black list
  char list = 0;
  //our current cstring
  unsigned char *cur_cstring = NULL;
  //our error(s)
  unsigned int error = 0;
  //because we rely on null :(
  unsigned int i = 0;
  //for moving along our cstring
  unsigned int j = 0;

  //it's sad i have to do this
  if(i == 0)
    return error;

  //initialize args
  va_start(args, num_cstrings);

  //are we using a white/black list?
  if(flags & RPI_PI_SANITIZE_CGI_LIST_WHITE || flags & RPI_PI_SANITIZE_CGI_LIST_BLACK)
  {
    //get first cstring
    list = va_arg(args, unsigned char*);
    //increment counter
    i++;
  }
  //default to alphanumeric white list
  else
  {
    list = rpi_pi_sanitize_cgi_build_list_white(1, "abcdefghijklmnopqrstuvwkyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
    flags | RPI_PI_SANITIZE_CGI_LIST_WHITE;
  }
  
  //iterate over cstring(s)
  for(i; i < num_cstrings; i++)
  {
    //grab a string
    cur_cstring = va_arg(args, unsigned char*);
    //reset our cstring index
    j = 0;
    while(cur_cstring[j] != '\0')
    {
      if(flags & RPI_PI_SANITIZE_CGI_LIST_WHITE)
      {
      }
    }
  }

  //returns number of invalid characters if wanted
  if(flags & RPI_PI_SANITIZE_CGI_WARN)
    return error;
  else
    return 0;
}

unsigned char* rpi_pi_sanitize_cgi_build_list(int value, char* list)
{
  //our list index
  unsigned int i = 0;
  //the list we will return
  unsigned char ret_list[33];

  //initialze our return list
  for(i = 0; i < 32; i++)
  {
    switch(value)
    {
      case 0:
        ret_list[i] = 255;
        break;

      case 1:
        ret_list[i] = 0;
        break;
      
      //defaults to white list
      default:
        ret_list[i] = 255;
        break;
    }
  }

  i = 0;

  while(list[i] != '\0')
  {
    //bit by bit...
    switch(value)
    {
      //black list
      case 0:
        //set the bit to 0 by anding with 11111110
        (ret_list+list[i])[0] = (ret_list+list[i])[0] & 254;
        break;

      
      case 1:
        //set the bit to 1 by oring with 00000001
        (ret_list+list[i])[0] = (ret_list+list[i])[0] | 1;
        break;

      //white list default
      default:
        (ret_list+list[i])[0]
        break;
  }
}
