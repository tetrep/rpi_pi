#include "parse_cgi.hpp" //for parse_cgi namespace
#include "parse_lpq.h" //for rpi_pi_parse_lpq_job_tok()
#include <iostream> //for std::cout, std::endl

//@brief we wan't to repeat the key-value pairs we read in and the command output
int main()
{
  try
  {
    //grab all our key-value pairs and store them
    parse_cgi::key_value_data key_value_pairs(parse_cgi::get_url_encoded_string());
  }
  catch(const std::exception &e)
  {
    //oh noes!
    std::cout << "=>" << e << std::endl << "-->" << e.what() << std::endl;

    return 1;
  }
  return 0;
}
