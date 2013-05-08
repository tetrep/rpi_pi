#remove our old binary from the cgi directory
rm -fv /cgi/mime.cgi &&

#compile it!
#we want all the warnings
#we want extra warnings
#we want warnings to be errors
#we want the sexy c++ standard
#we want to print all the errors
#we want to write everything to a log file
clang ++ -Wall -Wextra -Werror -std=c++11 -ferror-limit=0 mime.cpp parse_cgi_main.cpp -o mime.cgi &> cgi_build_log.txt &&

#copy our binary to the cgi directory
cp /cgi/rpi_pi/mime.cgi /cgi/mime.cgi &&

#REQUEST_METHOD tells us how we got the data, it will be GET, POST, or HEAD
#we will only be handling GET and POST requests
#GET requests store the data in the environment variable QUERY_STRING
#POST requests store the data in stdin
#the size of the data is stored in the environment variable CONTENT_LENGTH

#for these tests we will store the data in url_encoded
url_encoded="key=value;abc=123&doe=ray;me=far" &&

clear &&

#let's test GET
  export REQUEST_METHOD=GET &&
  export QUERY_STRING=${url_encoded} &&
  echo "${url_encoded}" | ./parse_cgi.out &&

#let's test POST
  export REQUEST_METHOD=POST &&
  export CONTENT_LENGTH=${#url_encoded} &&
  echo "${url_encoded}" | ./parse_cgi.out;
