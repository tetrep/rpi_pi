//include protection
#ifndef RPI_PI_EXECUTE_H
  #define RPI_PI_EXECUTE_h
  #include <stdarg.h>
  
  //@brief lists the queue for a given printer
  //@param args the va_list containig a user name and a printer
  //the user that will run this command
  //the printer we wish to view the queue of
  void *rpi_pi_execute_lpq(va_list *args);

  //@brief prints a given file to a given printer
  //@param args the va_list containing a user name, a printer, and a file
  //the user that will run this command
  //the printer we wish to send the file to
  //the file we wish to print
  void *rpi_pi_execute_lpr(va_list *args);

  //@brief cancels a given job from a given printer
  //@param args the va_list containing a user name, a printer, and a job id
  //the user that will run this command
  //the printer that has the job we want to cancel
  //the job we want to cancel
  void *rpi_pi_execute_lprm(va_list *args);

  //@brief forks the given function, piping its stdout to the parent
  //@param fp the function to be executed, must take a pointer to a va_list
  //@param ... the arguments for the function, the last one being NULL and all being pointers
  int rpi_pi_execute_forker(void *(*fp)(va_list*), ...);

  //@brief wrapper for execlp, runs given command as given user
  //@param user the user to run the command as
  //@param cmd the command to run as the given user
  void rpi_pi_execute_su_c(char */user*/, char */*cmd*/);

  //short function names
  #ifdef RPI_PI_EXECUTE_SHORT_NAMES
    #define lpq(...) rpi_pi_execute_lpq(__VA_ARGS__)
    #define lpr(...) rpi_pi_execute_lpr(__VA_ARGS__)
    #define lprm(...) rpi_pi_execute_lprm(__VA_ARGS__)
    #define forker(...) rpi_pi_execute_forker(__VA_ARGS__)
    #define su_c(...) rpi_pi_execute_su_c(__VA_ARGS__)
  #endif
#endif
