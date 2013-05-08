#include "parse_cgi.hpp" //for parse_cgi namespace
#include <iostream> //for std::cout, std::endl
#include <typeinfo> //for typeid
#include <utility> //for std::pair

//@brief outputs what we need for valid http
void html_output(std::string output)
{
  //we need to print this first
  std::cout << "Content-type: text/html" << std::endl
            //it's html!
            << "<html>" << std::endl
              //our title
              << "<title>TEST PAGE</title>" << std::endl
              //start of the body
              << "<body>" << std::endl
                //don't format our given output
                << "<code>" << std::endl
                  //actually print what we were given
                  << output << std::endl
                //close the code tag
                << "</code>"
              //close the body tag
              << "</body>" << std::endl
            //close the html tag
            << "</html>" << std::endl;
}

//@brief we wan't to repeat the key-value pairs we read in and the command output
int main()
{
  try
  {
    //grab all our key-value pairs and store them
    parse_cgi::key_value_data key_value_pairs(parse_cgi::get_url_encoded_string());

    //build a string of what we have
    std::string output("key=value");
    
    output = std::string("\n") + std::string("---------") + std::string("\n");
    for(auto p : key_value_pairs)
    {
      output + p.first + std::string("|") + p.second + std::string("\0");
    }

    //print out the string as valid html
    html_output(output);
  }
  catch(const std::exception &e)
  {
    html_output(typeid(e).name() + std::string("\n") + e.what());

    //we don't discriminate errors...
    return 0;
  }
  return 0;
}
