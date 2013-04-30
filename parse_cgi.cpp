#include "parse_cgi.hpp" //for parse_cgi::key_value_data

#include <exception> //for std::exception
#include <utility> //for std::pair
#include <string> //for std::string
#include <unordered_map> //for std::unordered_map
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

//fill the container with key-value pairs from url_encoded //@todo throw meaningful exceptions, handle exceptions
//@unique_ptr
void parse_cgi::key_value_data::parse_and_add(const std::string &url_encoded) throw(std::exception)
{
  //index to start look for key value pairs with
  size_t index = 0;
  //temporary storage for our found key-value pairs
  key_value_type key_value;

  try
  {
    //start looking for key-value pairs from index 0, afterwards start looking for the next key-value pair from the end of the last found key-value pair
    //an exception will be thrown when we reach the end
    index = 0;
    while(true)
    {
      //get a key_value from the string at the given index
      key_value = get_url_encoded_key_value(url_encoded, index);

      //set index to one after the end of the returned value
      //we need to do this now because we will lose the reference when we
      //add it to our container
      static_assert(std::is_same<key_type, std::string>::value, "we need the key to be a std::string");
      static_assert(std::is_same<value_type, std::string>::value, "we need the value to be a std::string");
      //now we can do our math, add 2 for the '=' and either the '&' or the ';'
      //we are relying on std::string::substr to throw an exception after we increment index too far, thus kicking us out of the loop
      index += key_value.first.size() + key_value.second.size() + 2;

      try
      {
        //add the key_value to our container
        this->add_key_value(key_value);
      }
      catch(const std::exception &e)
      {
        //something bad happened, reset the container
        this->clear_key_value_container();

        //somebody else's problem...
        throw e;
      }
    }
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
//@unique_ptr
parse_cgi::key_value_data::key_value_type parse_cgi::key_value_data::get_url_encoded_key_value(const std::string &url_encoded, const size_t index) throw(std::exception)
{
  try
  {
    //return a key_value_type consisting of the first key after the given index and the first value after the given index
    std::unique_ptr<key_type> temp_key = get_url_encoded_key(url_encoded, index);
    //@state_dependent, key_type=std::string
    static_assert(std::is_same<key_type, std::string>::value, "we use key_type.size() to optimize our search for a value by 'skipping' over the key by incrementing our starting index that we pass to get_url_encoded_value");
    //construct and return a unique_ptr using a new key_value_type using the key temp_key and the value returned by get_url_encoded_value
    return std::make_pair(*temp_key, *(get_url_encoded_value(url_encoded, index+temp_key->size()+1)));
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
    //find_first_of returns std::string::npos, which is size_t - 1, if it
    //doesn't find anything we just return the rest of the string, this
    //means exceptions are all fatal, this will not always be the case
    return std::unique_ptr<key_type>(new key_type(url_encoded.substr(index, std::min(url_encoded.find_first_of("=", index), url_encoded.size()-1) - index)));
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
    //find_first_of returns std::string::npos, which is size_t - 1, if it
    //doesn't find anything we just return the rest of the string, this
    //means exceptions are all fatal, this will not always be the case
    return std::unique_ptr<value_type>(new value_type(url_encoded.substr(index, std::min(url_encoded.find_first_of("&;", index), url_encoded.size()) - index)));
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
void parse_cgi::key_value_data::add_key_value(const key_type &key, const value_type &value) throw(std::exception)
{
  try
  {
    //attempt to add it to our hashmap
    std::pair<key_value_container_type::iterator, bool> temp_pair = this->key_value_container.emplace(key, value);
    //update the value of the key if we already have it in the map
    if(temp_pair.second == false)
      temp_pair.first->second = value;
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
void parse_cgi::key_value_data::add_key_value(const key_value_type &key_value) throw(std::exception)
{
  try
  {
    //decompose pair and call our sister function
    this->add_key_value(key_value.first, key_value.second);
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
    return this->key_value_container.begin();
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw e;
  }
}

//@todo throw meaningful exceptions, handle exceptions
void parse_cgi::key_value_data::clear_key_value_container() throw(std::exception)
{
  try
  {
    //empty the container
    this->key_value_container.clear();
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw e;
  }
}
