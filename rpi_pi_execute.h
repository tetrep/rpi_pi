//include protection
#ifndef RPI_PI_EXECUTE_H
  #define RPI_PI_EXECUTE_h
  
  //@brief lists the queue for a given printer
  //@param user the user that will run this command
  //@param printer the printer we wish to view the queue of
  void* rpi_pi_execute_lpq(char* /*user*/, char* /*printer*/);

  //@brief prints a given file to a given printer
  //@param user the user that will run this command
  //@param printer the printer we wish to send the file to
  //@param file the file we wish to print
  void* rpi_pi_execute_lpr(char* /*user*/, char* /*printer*/, void* /*file*/);

  //@brief cancels a given job from a given printer
  //@param printer the printer that has the job we want to cancel
  //@param job the job we want to cancel
  void* rpi_pi_execute_lprm(char* /*user*/, char* /*printer*/, char* /*job*/);

  //@brief forks the given function, piping its stdout to the parent
  //@param fp the function to be executed
  //@param ... the arguments for the function, the last one being NULL and all being pointers
  int rpi_pi_execute_forker(void* (*fp)(), ...);

  //short function names
  #ifdef RPI_PI_EXECUTE_SHORT_NAMES
    #define lpq(...) rpi_pi_execute_lpq(__VA_ARGS__)
    #define lpr(...) rpi_pi_execute_lpr(__VA_ARGS__)
    #define lprm(...) rpi_pi_execute_lprm(__VA_ARGS__)
    #define forker(...) rpi_pi_execute_forker(__VA_ARGS__)
  #endif
#endif
