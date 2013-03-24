#include "rpi_pi_parse_lpq.h"
#include "rpi_pi_execute.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//@TODO optimize, only search start of line, use printer, break into functions
char** rpi_pi_parse_lpq_job_tok(char *user, char *printer)
{
  //one line of input from lpq
  char line[100] = {'\0'};
  char *lpq_user = NULL, *job = NULL;
  //our return array
  char **ret = NULL;
  //current index in return array and max size of return array
  int index = 0, ret_max = 10;

  //have lpq output into stdin
  rpi_pi_execute_forker(rpi_pi_execute_lpq, user, printer, NULL);

  //grab a line of input
  while(fgets(line, 100, stdin) != NULL)
  {
    //only run on first input read from stdin
    if(ret == NULL)
    {
      ret = malloc(ret_max*sizeof(char*));
      if(ret == NULL)
        goto rpi_pi_parse_lpq_job_tok_mem_error;
    }

    //we want the line with the persons userid
    lpq_user = strstr(line, user);

    //did we find their name on this line?
    if(lpq_user != NULL)
    {
      //advance to "job"
      job = strstr(lpq_user, "job");

      //did we find the string "job"?
      if(job != NULL)
      {
        //grab the job ID
        job = strtok(&job[3], " ]");

        //did we find a job id?
        if(job != NULL)
        {
          //do we need to allocate more memory?
          if(index >= ret_max)
          {
            //double it! i miss std::vector :(
            ret_max += ret_max;

            if(realloc(ret, ret_max*sizeof(char*)) == NULL)
              goto rpi_pi_parse_lpq_job_tok_unspool;
          }

          //allocate memory for the job id
          ret[index] = malloc(strlen(job)*sizeof(char)+1);

          //download more ram please
          if(ret[index] == NULL)
          {
            //we dont need to free the current index
            index--;
            goto rpi_pi_parse_lpq_job_tok_unspool;
          }

          //make it a cstring
          ret[index][0] = '\0';
          
          //copy the job id into the return array
          strcpy(ret[index], job);

          //increment index
          index++;
        }
      }
    }
  }

  //null terminate ret array if it exists
  if(ret != NULL)
  {
    //do we have enough room?
    if(index >= ret_max)
    {
      //grab one more slot
      ret_max++;
      if(realloc(ret, ret_max*sizeof(char*)) == NULL)
        goto rpi_pi_parse_lpq_job_tok_unspool;
    }

    //null terminate array
    ret[index] = NULL;
  }

  //no memory errors, woo!
  return ret;

  rpi_pi_parse_lpq_job_tok_unspool:
    //free our wonderful return array
    if(ret != NULL)
    {
      //free the "inner" array
      while(index > -1)
      {
        free(ret[index]);
        index--;
      }
      //free the OG pointer
      free(ret);
    }

  rpi_pi_parse_lpq_job_tok_mem_error:
    perror("PARSE LPQ ERROR: OUT OF MEMORY\n");
    return NULL;
}
