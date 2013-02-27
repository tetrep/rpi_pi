#include "rpi_pi_parse_lpq.h"
#include "rpi_pi_execute.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* rpi_pi_parse_lpq_job_tok(char* user, char* printer, char* place)
{
  //one line of input from lpq
  char line[100];
  char *lpq_user = NULL, *job = NULL;

  //have lpq output into stdin
  rpi_pi_execute_forker(rpi_pi_execute_lpq, user, printer, NULL);

  fgets(line, 100, stdin);// != NULL
  {
    //we want the line with the persons userid
    lpq_user = strstr(line, user);
    if(lpq_user != NULL)
    {
      //advance to "job"
      job = strstr(line, "job");
      if(job != NULL)
        job = strtok(&job[3], "]");
    }
  }

    if(lpq_user != NULL)
      printf("user: %s\n", lpq_user);

    if(job != NULL)
      printf("job: %s\n", job);

    if(lpq_user != NULL)
      free(lpq_user);
    if(job != NULL)
      free(job);

  return place;
}
