#include "parse_cgi.hpp"

//default constructor, empty
parse_cgi::key_value_data::key_value_data()
{
}

//fills the container with key-value pairs from url_encoded
//@todo throw meaningful exceptions, handle exceptions
parse_cgi::key_value_data::key_value_data(const &std::string url_encoded) throw(std::exception)
{
  try
  {
    parse_and_add(url_encoded);
  }
  catch(const &std::exception e)
  {
    //somebody else's problem...
    throw e;
  }
}

//fill the container with key-value pairs from url_encoded
//@todo throw meaningful exceptions, handle exceptions
void parse_cgi::key_value_data::parse_and_add(const &std::string url_encoded) throw(std::exception)
{
  //index to start look for key value pairs with
  size_t index = 0;
  //our return data
  std::tuple<key_value_type, size_t> return_data = NULL;

  try
  {
    for(index = 0; index < url_encoded.size()-1; index = std::get<2>(return_data))
    {
      //get a key_value from the string at the given index
      return_data = parse_key_value(url_encoded, index);
      //if the key_value isn't null, add it to our container
      if(std::get<1>(return_data) != NULL)
        this->key_values.push_back(std::get<1>(return_data));
      //we ran out of key-value pairs, setting this will kill the for loop
      else
        std::get<2>(return_data) = url_encoded.size();
    }
  }
  catch (const &std::exception e)
  {
    //something bad happened, reset the container
    this->key_values.clear();

    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
std::tuple<parse_cgi::key_value_data::key_value_type, size_t> parse_cgi::key_value_data::parse_key_value(const &std::string url_encoded, const size_t index) throw(std::exception)
{
  try
  {
    return std::make_tuple(get_url_encoded_key(url_encoded, index), get_url_encoded_value(url_encoded, index));
  }
  catch(const &std::exception)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
parse_cgi::key_value_data::key_type parse_cgi::key_value_data::get_url_encoded_key(const &std::string url_encoded, const size_t index) throw(std::exception)
{
  try
  {
    return url_encoded.substr(index, url_encoded.find_first_of("=", index) - index+1);
  }
  catch(const &std::exception e)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
parse_cgi::key_value_data::key_type parse_cgi::key_value_data::get_url_encoded_key(const &std::string url_encoded, const size_t index) throw(std::exception)
{
  try
  {
    //we want the string between the first '=' and the first '&' or ';'
    size_t temp_index = url_encoded.find_first_of("=", index);
    return url_encoded.substr(temp_index, url_encoded.find_first_of("&;", temp_index+1) - temp_index+1);
  }
  catch(const &std::exception e)
  {
    //somebody else's problem...
    throw e;
  }
}
