//include protection
#ifndef RPI_PI_EXECUTE_H
  #define RPI_PI_EXECUTE_h
  
  //@brief lists the queue for a given printer
  //@param user the user that will run this command
  //@param printer the printer we wish to view the queue of
  int rpi_pi_lpq(char* /*user*/, char* /*printer*/);
  //@brief prints a given file to a given printer
  //@param user the user that will run this command
  //@param printer the printer we wish to send the file to
  //@param file the file we wish to print
  int rpi_pi_lpr(char* /*user*/, char* /*printer*/, void* /*file*/);
  //@brief cancels a given job from a given printer
  //@param printer the printer that has the job we want to cancel
  //@param job the job we want to cancel
  int rpi_pi_lprm(char* /*user*/, char* /*printer*/, char* /*job*/);

  //short function names
  #ifdef RPI_PI_EXECUTE_SHORT_NAMES
    #define lpq(...) rpi_pi_lpq(__VA_ARGS__)
    #define lpr(...) rpi_pi_lpr(__VA_ARGS__)
    #define lprm(...) rpi_pi_lprm(__VA_ARGS__)
  #endif
#endif
