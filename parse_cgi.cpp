#include "parse_cgi.hpp" //for parse_cgi::key_value_data

#include <exception> //for std::exception
#include <tuple> //for std::tuple, std::get
#include <string> //for std::string
#include <list> //for std::list
#include <memory> //for std::unique_ptr
#include <algorithm> //for std::min
#include <type_traits> //for static_assert, std::is_same

//if i ever feel like indenting everything
//i should put this all in the parse_cgi namespace

//default constructor, empty
parse_cgi::key_value_data::key_value_data()
{
}

//fills the container with key-value pairs from url_encoded
//@todo throw meaningful exceptions, handle exceptions
parse_cgi::key_value_data::key_value_data(const std::string &url_encoded) throw(std::exception)
{
  try
  {
    //add all the key-value pairs in url_encoded to our data structure
    parse_and_add(url_encoded);
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw e;
  }
}

//fill the container with key-value pairs from url_encoded
//@todo throw meaningful exceptions, handle exceptions
//@unique_ptr
void parse_cgi::key_value_data::parse_and_add(const std::string &url_encoded) throw(std::exception)
{
  //index to start look for key value pairs with
  size_t index = 0;
  //our return data
  std::unique_ptr<std::tuple<key_value_type, size_t> > return_data;

  try
  {
    //start looking for key-value pairs from index 0, afterwards start looking for the next key-value pair from the end of the last found key-value pair
    //an exception will be thrown when we reach the end
    index = 0;
    while(true)
    {
      //get a key_value from the string at the given index
      return_data = parse_key_value(url_encoded, index);

      //add the key_value to our container
      this->add_key_value(std::get<0>(*return_data));

      //set index to one after the end of the returned value
      index = std::get<1>(*return_data) + 1;
    }
  }
  catch(const std::exception &e)
  {
    //the exception was not from reaching the end
    //RECONCILE PLOX
    if(true)
    {
      //something bad happened, reset the container
      this->clear_key_values();

      //somebody else's problem...
      throw e;
    }
  }
}

//@todo throw meaningful exceptions, handle exceptions
//@unique_ptr
std::unique_ptr<std::tuple<std::unique_ptr<parse_cgi::key_value_data::key_value_type>, size_t> > parse_cgi::key_value_data::parse_key_value(const std::string &url_encoded, const size_t index) throw(std::exception)
{
  try
  {
    //return a unique_ptr of the key_value_type consisting of the first key after the given index and the first value after the given index
    std::unique_ptr<key_type> temp_key = get_url_encoded_key(url_encoded, index);
    //@state_dependent, key_type=std::string
    static_assert(std::is_same(key_type, std::string), "we use key_type.size() to optimize our search for a value by 'skipping' over the key by incrementing our starting index that we pass to get_url_encoded_value");
    return new std::unique_ptr<key_value_type>(new key_value_type(temp_key, get_url_encoded_value(url_encoded, index+(*temp_key).size())));
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
//@unique_ptr
std::unique_ptr<parse_cgi::key_value_data::key_type> parse_cgi::key_value_data::get_url_encoded_key(const std::string &url_encoded, const size_t index) throw(std::exception)
{
  try
  {
    //starting at index, generate a substring until we hit an '=' or the end of the string, this is our key, return it
    return std::unique_ptr<key_type>(new key_type(url_encoded.substr(index, std::min(url_encoded.find_first_of("=", index), url_encoded.size()) - index)));
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
//@unique_ptr
std::unique_ptr<parse_cgi::key_value_data::value_type> parse_cgi::key_value_data::get_url_encoded_value(const std::string &url_encoded, const size_t index) throw(std::exception)
{
  try
  {
    //return a string starting at the given index and stopping before the first '&' or ';' or the end of url_encoded
    return std::unique_ptr<value_type>(new value_type(url_encoded.substr(index, std::min(url_encoded.find_first_of("&;", index), url_encoded.size()) - index));
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
//@unique_ptr
void parse_cgi::key_value_data::add_key_value(const key_type &key, const value_type &value) throw(std::exception)
{
  try
  {
    //give our sister function a unique_ptr
    this->add_key_value(std::unique_ptr<key_value_type>(new key_value_type(key, value)));
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
//@unique_ptr
void parse_cgi::key_value_data::add_key_value(std::unique_ptr key_value) throw(std::exception)
{
  try
  {
    //push the tuple to the back of our list
    this->key_values.push_back(key_value);
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
parse_cgi::key_value_data::key_value_container_type::iterator parse_cgi::key_value_data::get_iterator() throw(std::exception)
{
  try
  {
    return this->key_values.begin();
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw e;
  }
}
