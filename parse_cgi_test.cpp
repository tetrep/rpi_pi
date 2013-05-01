#include "parse_cgi.hpp" //for parse_cgi namespace
#include <iostream> //for std::cout, std::endl
#include <exception> //for std::exception
#include <typeinfo> //for typeid

//@brief lets get some linker action going
int main()
{
  try
  {
    //test environment variable reading
    std::string test_url_encoded = parse_cgi::get_url_encoded_string();

    //test constructor/parsing
    parse_cgi::key_value_data test_data(test_url_encoded);

    std::cout << "look what we found..." << std::endl;
    //print what we found in get_test_data
    for(auto &x : test_data)
      std::cout << x.first << ":" << x.second << std::endl;
  }
  catch(const std::exception &e)
  {
    //we've run out of stack to unwind :(
    std::cout << "=>" << typeid(e).name() << std::endl
      << "-->" << e.what() << std::endl;
  }

  return 0;
}
