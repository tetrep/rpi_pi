#include "parse_cgi.hpp" //for parse_cgi namespace

#include <exception> //for std::exception
#include <utility> //for std::pair
#include <string> //for std::string
#include <unordered_map> //for std::unordered_map
#include <memory> //for std::unique_ptr
#include <algorithm> //for std::min(), std::max()
#include <type_traits> //for static_assert(), std::is_same
#include <cstdlib> //for getenv()
#include <iostream> //for std::in
#include <iterator> //for std::istreambuf_iterator

//if i ever feel like indenting everything
//i should put this all in the parse_cgi namespace

//default constructor, empty
parse_cgi::key_value_data::key_value_data()
{
}

//@todo throw meaningful exceptions, handle exceptions
parse_cgi::key_value_data::key_value_data(const std::string &url_encoded)
{
  try
  {
    //add all the key-value pairs in url_encoded to our data structure
    parse_and_add(url_encoded);
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

//@todo optimize
void parse_cgi::key_value_data::parse_and_add(const std::string &url_encoded)
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

      //add the key_value to our container
      this->add_key_value(key_value);
    }
  }
  //it's benign, no problems
  catch(const benign_exception &e)
  {
    //we don't have any problems, just leave the function
    return;
  }
  //we ran out of memory :(
  catch(const std::bad_alloc &e)
  {
    //free up our container in case somebody else needs memory
    //while we unwind the stack
    this->clear_key_value_container();

    //somebody else's problem...
    throw;
  }
  //not a memory issue, we can keep our key-value pairs
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
parse_cgi::key_value_data::key_value_type parse_cgi::key_value_data::get_url_encoded_key_value(const std::string &url_encoded, const size_t index)
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
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
std::unique_ptr<parse_cgi::key_value_data::key_type> parse_cgi::key_value_data::get_url_encoded_key(const std::string &url_encoded, const size_t index)
{
  try
  {
    //starting at index, generate a substring until we hit an '=' or the end of the string, this is our key, return it
    //find_first_of returns std::string::npos, which is size_t - 1, if it
    //doesn't find anything we just return the rest of the string
    return std::unique_ptr<key_type>(new key_type(url_encoded.substr(index, std::min(url_encoded.find_first_of("=", index), url_encoded.size()-1) - index)));
  }
  //to whom it may concern, nothing bad happened
  catch(const std::out_of_range &e)
  {
    //somebody elses's not problem...
    throw benign_exception();
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
std::unique_ptr<parse_cgi::key_value_data::value_type> parse_cgi::key_value_data::get_url_encoded_value(const std::string &url_encoded, const size_t index)
{
  try
  {
    //return a string starting at the given index and stopping before the first '&' or ';' or the end of url_encoded
    //find_first_of returns std::string::npos, which is size_t - 1, if it
    //doesn't find anything we just return the rest of the string
    return std::unique_ptr<value_type>(new value_type(url_encoded.substr(index, std::min(url_encoded.find_first_of("&;", index), url_encoded.size()) - index)));
  }
  //to whom it may concern, nothing bad happened
  catch(const std::out_of_range &e)
  {
    //somebody elses's not problem...
    throw benign_exception();
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
void parse_cgi::key_value_data::add_key_value(const key_type &key, const value_type &value)
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
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
void parse_cgi::key_value_data::add_key_value(const key_value_type &key_value)
{
  try
  {
    //decompose pair and call our sister function
    this->add_key_value(key_value.first, key_value.second);
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
parse_cgi::key_value_data::key_value_container_type::iterator parse_cgi::key_value_data::begin()
{
  try
  {
    //return an iterator pointing to the beginning of the container
    return this->key_value_container.begin();
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
parse_cgi::key_value_data::key_value_container_type::iterator parse_cgi::key_value_data::end()
{
  try
  {
    //return an iterator pointing to the end of the container
    return this->key_value_container.end();
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
parse_cgi::key_value_data::value_type parse_cgi::key_value_data::get_value(const parse_cgi::key_value_data::key_type &key)
{
  try
  {
    //the iterator to the key-value pair we are looking for
    key_value_container_type::const_iterator it = this->key_value_container.find(key);

    //if key_value_container.end() is returned, we didn't find it
    if(it != key_value_container.end())
    {
      //we found it, return the value
      return it->second;
    }
    //we didn't find it
    else
    {
      throw key_not_found_exception();
    }
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
parse_cgi::key_value_data::value_type parse_cgi::key_value_data::pop_value(const parse_cgi::key_value_data::key_type &key)
{
  try
  {
    //the value we will return
    key_value_container_type::iterator it = this->key_value_container.find(key);

    //if key_value_container.end() is returned, we didn't find it
    if(it != key_value_container.end())
    {
      //we found it, save it
      value_type ret = it->second;

      //kill it
      this->key_value_container.erase(it);

      //return what we found
      return ret;
    }
    else
    {
      throw key_not_found_exception();
    }
  }
  catch(const std::exception &e)
  {
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
void parse_cgi::key_value_data::clear_key_value_container()
{
  try
  {
    //empty the container
    this->key_value_container.clear();
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
std::string parse_cgi::get_url_encoded_string()
{
  try
  {
    //how did we get the data?
    std::string request_method = get_environment_variable("REQUEST_METHOD");

    //was the data sent to us via GET?
    if(request_method == "GET")
    {
      return get_url_encoded_string_via_get();
    }
    //was the data sent to us via POST?
    else if(request_method == "POST")
    {
      return get_url_encoded_string_via_post();
    }
    //in case we decided to support HEAD
    else if(request_method == "HEAD")
    {
      return get_url_encoded_string_via_head();
    }
    //we tried :(
    else
    {
      throw std::runtime_error("REQUEST_METHOD has an invalid value of "+request_method);
    }
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
std::string parse_cgi::get_url_encoded_string_via_get()
{
  try
  {
    //our url-encoded data is in the environment variable QUERY_STRING
    return get_environment_variable("QUERY_STRING");
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
std::string parse_cgi::get_url_encoded_string_via_post()
{
  try
  {
    //no need to ask twice...
    size_t content_length = std::atoi(get_environment_variable("CONTENT_LENGTH").c_str());

    //we need to store our c_str because the std::string constructor is bad
    //we're going to abuse unique_ptr a little here...
    std::unique_ptr<char> c_str(new char[content_length+1]);

    //read content_length characters from stdin
    std::cin.read(&(*c_str), content_length);
    //make it a c_str
    (&(*c_str))[content_length] = '\0';

    //return our newly found data
    return std::string(&(*c_str));
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
std::string parse_cgi::get_url_encoded_string_via_head()
{
  try
  {
    //we don't support head...
    throw std::logic_error("head is not supported");
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

//@todo throw meaningful exceptions, handle exceptions
std::string parse_cgi::get_environment_variable(const std::string &env)
{
  try
  {
    //need to save it so we can check if it is null
    char *c_str = getenv(env.c_str());

    //because the std::string::string really hates error checking
    if(c_str == nullptr)
      throw std::invalid_argument("std::string::string(const char *) cannot handle the awesomeness that is nullptr");

    return std::string(c_str);
  }
  catch(const std::exception &e)
  {
    //somebody else's problem...
    throw;
  }
}

const char* parse_cgi::benign_exception::what() const noexcept
{
  return "nothing wrong here";
}

const char* parse_cgi::key_value_data::key_not_found_exception::what() const noexcept
{
  return "the key was not found";
}
