#include "parse_cgi.hpp" //for parse_cgi namespace
#include <iostream> //for std::cout, std::endl
#include <exception> //for std::exception
#include <typeinfo> //for typeid

//@brief lets get some linker action going
int main()
{
  try
  {
    //test constructor/parsing
    parse_cgi::key_value_data test("key=value;abc=123&doe=ray;fah=lah");

    //test accessing container
    for(auto &x : test)
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
