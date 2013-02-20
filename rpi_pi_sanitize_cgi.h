//@file rpi pi sanitize cgi header file

//include protection
#ifndef RPI_PI_SANITIZE_CGI_H
  #define RPI_PI_SANITIZE_CGI_H

  //for use in sanitize_cgi function
    //returns the number of invalid characters found
    #define RPI_PI_SANITIZE_CGI_WARN 1
    //treat the first cstring as a white list of acceptable characters
    //if both black and white are set, white will be used
    #define RPI_PI_SANITIZE_CGI_LIST_WHITE 2
    //treat the first cstring as a black list of unacceptable characters
    #define RPI_PI_SANITIZE_CGI_LIST_BLACK 4

  //@brief sanitizes the given cstrings
  //@param flags any needed predefined flags, or'd together
  int rpi_pi_sanitize_cgi(unsigned int /*flags*/, unsigned int /*num_cstrings*/, ...);
  //@brief builds a bit list of acceptable characters, returned list needs to be freed!!!!!!
  //@param value the desired value to set the bits, 0 for black list 1 for white list
  //@param list the list of characters to be given the given value
  char* rpi_pi_sanitize_cgi_build_list(unsigned int /*value*/, char* /*list*/);

  //short names
  #ifdef RPI_PI_SANITIZE_CGI_SHORT_NAMES
    #define sanitize_cgi(...) rpi_pi_sanitize_cgi(__VA_ARGS__)
    #define build_list(...) rpi_pi_sanitize_cgi_build_list(__VA_ARGS__)
  #endif

#endif
