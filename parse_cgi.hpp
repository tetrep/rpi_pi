#ifndef PARSE_CGI_HPP
  #define PARSE_CGI_HPP

  #include <exception> //for std::exception
  #include <utility> //for std::pair
  #include <unordered_map> //for std::unordered_map
  #include <string> //for std::string
  #include <memory> //for std::unique_ptr

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
      using key_value_type = std::pair<key_type, value_type>;
      //the type of our container
      using key_value_container_type = std::unordered_map<key_type, value_type>;

      public:
        //@brief default constructor
        key_value_data();
        //@brief adds all the key_value pairs in url_encoded to our class container
        //@param url_encoded a url-encoded string of key_value pairs
        key_value_data(const std::string &url_encoded);

        //@brief add all the key_value pairs in url_encoded to our class container
        //@param url_encoded a url-encoded string of key_value pairs
        void parse_and_add(const std::string &url_encoded);

        //@brief add a key and value to our data structure
        //@param key the key to be added
        //@param value the value to be added
        void add_key_value(const key_type &key, const value_type &value);
        //@brief add a key_value to our data structure from a pair
        //@param key_value the pair containing the key-value pair to be added
        void add_key_value(const key_value_type &key_value);
        //@brief empties our container of all key-value pairs
        void clear_key_value_container();

        //@brief get the begin() iterator from our container
        //@return returns an iterator to the beginning of our container
        key_value_container_type::iterator begin();
        //@brief get the end() iterator from our container
        //@return returns an iterator to the end of our container
        key_value_container_type::iterator end();

        //our helper functions
        //@brief return the first key-value pair found in the given string starting at the given index
        //@param url_encoded a url-encoded string
        //@param index the location (inclusive) to start looking for a key_value
        //@return returns the first key-value pair found
        key_value_type get_url_encoded_key_value(const std::string &url_encoded, const size_t index);
        //@brief return the first key found in the given string starting at the given index
        //@param url_encoded a url-encoded string
        //@param index the location (inclusive) to start looking for a key
        //@return returns a pointer to the first key found
        //@unique_ptr
        std::unique_ptr<key_type> get_url_encoded_key(const std::string &url_encoded, const size_t index);
        //@brief return the first value found in the given string starting at the given index
        //@param url_encoded a url-encoded string
        //@param index the location (inclusive) to start looking for a key
        //@return returns a pointer to the first value found
        //@unique_ptr
        std::unique_ptr<value_type> get_url_encoded_value(const std::string &url_encoded, const size_t index);

      private:
        //where we will store all our key-value pairs
        key_value_container_type key_value_container;
    };

    //our custom exception class, not thrown when something bad happens
    class cgi_benign : std::exception
    {
      const char* what() const noexcept;
    };

    //@brief returns the value of the given encironment variable
    //@param env the name of the environment variable to get
    //@return returns a std::string of the value of the given environment variable
    std::string get_environment_variable(const std::string &env);
    //@brief gets the url-encoded data as a std::string
    //@return returns a url-encoded std::string
    std::string get_url_encoded_string();
    //@brief gets the url-encoded data as a string if it has been given to us via POST
    //@return returns a url-encoded std::string
    std::string get_url_encoded_string_via_get();
    //@brief gets the url-encoded data as a string if it has been given to us via POST
    //@return returns a url-encoded std::string
    std::string get_url_encoded_string_via_post();
    //@brief gets the url-encoded data as a string if it has been given to us via HEAD
    //@return returns a url-encoded std::string
    std::string get_url_encoded_string_via_head();
  }
#endif
