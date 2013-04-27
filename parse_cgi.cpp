#include "parse_cgi.hpp"

//if i ever feel like indenting everything
//i should put this all in the parse_cgi namespace

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
    //add all the key-value pairs in url_encoded to our data structure
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
  std::tuple<key_value_type, size_t> return_data;

  try
  {
    //start looking for key-value pairs from index 0, afterwards start looking for the next key-value pair from the end of the last found key-value pair
    for(index = 0; index < url_encoded.size()-1; index = std::get<2>(return_data))
    {
      //get a key_value from the string at the given index
      return_data = parse_key_value(url_encoded, index);
      //if the key_value isn't null, add it to our container
      if(std::get<1>(return_data) != NULL)
        this->add_key_value(std::get<1>(return_data));
      //we ran out of key-value pairs, setting this will kill the for loop
      else
        std::get<2>(return_data) = url_encoded.size();
    }
  }
  catch(const &std::exception e)
  {
    //something bad happened, reset the container
    this->clear_key_values();

    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
std::tuple<parse_cgi::key_value_data::key_value_type, size_t> parse_cgi::key_value_data::parse_key_value(const &std::string url_encoded, const size_t index) throw(std::exception)
{
  try
  {
    //return a tuple consisting of the first key after the given index and the first value after the given index
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
    //starting at index, generate a substring until we hit an '=', this is our key, return it
    return url_encoded.substr(index, url_encoded.find_first_of("=", index) - index);
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
    //we want the string between the first '=' and the first '&' or ';', this is our value
    size_t temp_index = url_encoded.find_first_of("=", index);
    //construct a string starting after the first '=' and stopping before the first '&' or ';'
    return url_encoded.substr(temp_index+1, url_encoded.find_first_of("&;", temp_index) - temp_index+1);
  }
  catch(const &std::exception e)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
void parse_cgi::key_value_data::add_key_value(const &key_type key, const &value_type value) throw(std::exception)
{
  try
  {
    //give our sister function a tuple of the given key-value pair
    this->add_key_value(std::make_tuple(key, value));
  }
  catch(const &std::exception e)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
//STATE_DEPENDENT_FUNCTION
void parse_cgi::key_value_data::add_key_value(const &key_value_type key_value) throw(std::exception)
{
  try
  {
    //push the tuple to the back of our vector
    //STATE_DEPENDENT
    this-key_values.push_back(key_value);
  }
  catch(const &std::exception e)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
//STATE_DEPENDENT_FUNCTION
parse_cgi::key_value_data::key_value_container_type::iterator parse_cgi::key_value_data::get_iterator() throw(std::exception)
{
  try
  {
    //STATE_DEPENDET
    return this->key_values.begin();
  }
  catch(const &std::exception e)
  {
    //somebody else's problem...
    throw e;
  }
}
