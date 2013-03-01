#include "rpi_pi_sanitize_cgi.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int rpi_pi_sanitize_cgi(unsigned int flags, ...)
{
  //all our cstrings
  va_list args;
  //our white/black list
  char *list = NULL;
  //our current cstring
  char *cur_cstring = NULL;
  //our error(s)
  unsigned int error = 0;
  //for moving along our cstring
  unsigned int i = 0;

  //initialize args
  va_start(args, flags);

  //white list?
  if(flags & RPI_PI_SANITIZE_CGI_LIST_WHITE)
  {
    //get first cstring and make a white list from it
    list = rpi_pi_sanitize_cgi_build_list(1, va_arg(args, char*));
  }
  //black list?
  else if(flags & RPI_PI_SANITIZE_CGI_LIST_BLACK)
  {
    //get first cstring and make a black list from it
    list = rpi_pi_sanitize_cgi_build_list(0, va_arg(args, char*));
  }
  //default to alphanumeric white list
  else
  {
    list = rpi_pi_sanitize_cgi_build_list(1, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
  }

  //do we have a list to check against?
  if(list == NULL)
  {
    va_end(args);
    return -1;
  }

  //iterate over cstring(s)
  cur_cstring = va_arg(args, char*);
  while(cur_cstring != NULL)
  {
    //reset our cstring index
    i = 0;
    while(cur_cstring[i] != '\0')
    {
      //is it an invalid character?
      if(!((list+cur_cstring[i])[0] & 1))
      {
        //sanitize!
        cur_cstring[i] = '\0';
        //increment error counter
        error++;
      }
      i++;
    }

    //grab another cstring
    cur_cstring = va_arg(args, char*);
  }

  //memory managment!
  if(list != NULL)
    free(list);
  va_end(args);

  //returns number of invalid characters if wanted
  if(flags & RPI_PI_SANITIZE_CGI_WARN)
    return error;
  else
    return 0;
}

char *rpi_pi_sanitize_cgi_build_list(unsigned int value, char *list)
{
  //our list index
  unsigned int i = 0;
  //the list we will return
  char *ret_list = NULL;

  //do we have anything to do?
  if(list == NULL)
    return NULL;

  //allocate memory for our list
  ret_list = malloc(17);
  if(ret_list == NULL)
    return NULL;

  //initialze our return list
  for(i = 0; i < 17; i++)
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
        //set the bit to 0 by anding with the byte 11111110
        (ret_list+list[i])[0] = (ret_list+list[i])[0] & 254;
        break;

      
      case 1:
        //set the bit to 1 by oring with the byte 00000001
        (ret_list+list[i])[0] = (ret_list+list[i])[0] | 1;
        break;

      //white list default
      default:
        //set the bit to 1 by oring with the byte 00000001
        (ret_list+list[i])[0] = (ret_list+list[i])[0] | 1;
        break;
    }

    i++;
  }

  return ret_list;
}
