#ifndef PARSE_CGI_HPP
  #define PARSE_CGI_HPP

  #include <exception>
  #include <utility> //for tuples
  #include <vector>
  #include <string>

  //our lovely home
  namespace parse_cgi
  {
    //@brief all the data we need to pass between function calls
    class key_value_data
    {
      //the type of our keys
      using key_type = std::string;
      //the type of our values
      using value_type = std::string;
      //the type of our key-value pairs
      using key_value_type = std::tuple<key_type, value_type>

      public:
        //@brief default constructor
        key_value_data();
        //@brief adds all the key_value pairs in url_encoded to our class container
        //@param url_encoded a url-encoded string of key_value pairs
        key_value_data(const &std::string url_encoded);

        //@brief add all the key_value pairs in url_encoded to our class container
        //@param url_encoded a url-encoded string of key_value pairs
        void parse_and_add(const &std::string url_encoded);

        //@brief add a key_value to our data structure
        void add_key_value(const &key_type key, const &value_type value);
        //@brief add a key_value to our data structure from a tuple
        void add_key_value(const &key_value_type);

        //@brief return the key value at the given index
        key_value_type get_key_value(const unsigned int index);
        //@brief pop the key_value at the given index
        key_value_type pop_key_value(const unsigned int index);
        //@brief return the first key_value
        key_value_type get_first_key_value();
        //@brief pop the first key_value
        key_value_type pop_first_key_value();
        //@brief return the last key_value
        key_value_type get_last_key_value();
        //@brief pop the last key_value
        key_value_type pop_last_key_value();

        //our lone helper
        //@brief return the first key_value found in the given string starting at the given index
        //@param url_encoded a url-encoded string
        //@param index the location (inclusive) to start looking for a key_value
        key_value_type parse_key_value(const &std::string url_encoded, const unsigned int index) const;

      private:
        //vector of all the key/value pairs (tuples) we have found so far
        std::vector <key_value_type> key_values;
    };

    //@brief returns the value of the given encironment variable
    //@param env the name of the environment variable to get
    //@return returns a std::string of the value of the given environment variable
    std::string get_environment_variable(const &std::string env);
    //@brief gets the url_encoded string from either stdin or the environment variable QUERY_STRING depending on the environment variable REQUEST_METHOD
    //@return returns a std::string of url_encoded key-value pairs
    std::string get_url_encoded_string();
  }
#endif
