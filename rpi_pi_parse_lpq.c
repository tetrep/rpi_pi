#include "rpi_pi_parse_lpq.h"
#include "rpi_pi_execute.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//@TODO optimize
char** rpi_pi_parse_lpq_job_tok(char *user, char *printer)
{
  //one line of input from lpq
  char line[100] = {'\0'};
  char *lpq_user = NULL, *job = NULL;
  //our return array
  char **ret;
  int index = 0, ret_max = 10;

  //lets start with 10
  ret = calloc(10, sizeof(char*));

  //we only want 10 bytes :(
  if(ret == NULL)
    goto rpi_pi_parse_lpq_job_tok_mem_error;

  //have lpq output into stdin
  rpi_pi_execute_forker(rpi_pi_execute_lpq, user, printer, NULL);

  //grab a line of input
  while(fgets(line, 100, stdin) != NULL)
  {
    //we want the line with the persons userid
    lpq_user = strstr(line, user);

    //did we find their name on this line?
    if(lpq_user != NULL)
    {
      //advance to "job"
      job = strstr(line, "job");

      //did we find the string "job"?
      if(job != NULL)
      {
        //grab the job ID
        job = strtok(&job[3], "]");

        //did we find a job id?
        if(job != NULL)
        {
          //allocate memory for the job id
          ret[index] = calloc(strlen(job), sizeof(char));

          //copy the job id into the return array
          strcpy(ret[index], job);

          //increment index
          index++;

          //do we need to allocate more memory?
          if(index >= ret_max)
          {
            //double it! i miss std::vector :(
            ret_max += ret_max;
            ret = realloc(ret, (ret_max)*sizeof(char));

            if(ret == NULL)
              goto rpi_pi_parse_lpq_job_tok_mem_error;
          }

          //download more ram please
          if(ret[index] == NULL)
            goto rpi_pi_parse_lpq_job_tok_unspool;

        }
      }
    }
  }

  rpi_pi_parse_lpq_job_tok_unspool:
    //free our wonderful return array
    if(ret != NULL)
    {
      while(index != 0)
      {
        free(ret[index]);
        index--;
      }
      free(ret[index]);
      free(ret);
    }

  rpi_pi_parse_lpq_job_tok_mem_error:
}
