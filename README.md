rpi_pi
======

plain and boring interface for RPI's printers

decided to break my c89(ish) prison for the cgi, i'll be using c++ sparingly to integrate it into the rest of the program. exceptions are nice.

todo:
-------
=minor refactoring to clean up some functions
=print out html
  -probably want to use a class for this so i can easily pass around strings with html tags
=kerberos authentication (frontend)

api:
-----
action
userid
ticket
printer
file
