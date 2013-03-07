#ifndef RPI_PI_PARSE_LPQ_H
  #define RPI_PI_PARSE_LPQ_H
  //@brief compiles a list of jobs from the user on the given printer
  //@param user id that owns the jobs
  //@param printer the name of the printer to check
  char **rpi_pi_parse_lpq_job_tok(char */*user*/, char */*printer*/);
#endif
