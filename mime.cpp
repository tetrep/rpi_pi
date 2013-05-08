#include "parse_cgi.hpp" //for parse_cgi namespace
#include "parse_lpq.h" //for rpi_pi_parse_lpq_job_tok()
#include <iostream> //for std::cout, std::endl
#include <typeinfo> //for typeid

//@brief we wan't to repeat the key-value pairs we read in and the command output
int main()
{
  try
  {
    //grab all our key-value pairs and store them
    parse_cgi::key_value_data key_value_pairs(parse_cgi::get_url_encoded_string());

    //print out what we got
    std::cout << "key=value" << std::endl
              << "---------" << std::endl;
    for(parse_cgi::key_value_data::key_value_container_type::iterator it : key_value_pairs)
    {
      std::cout << it->first << "|" << it->second << std::endl;
    }
  }
  catch(const std::exception &e)
  {
    //oh noes!
    std::cout << "=>" << typeid(e).name() << std::endl << "-->" << e.what() << std::endl;

    //we don't discriminate errors...
    return 1;
  }
  return 0;
}
