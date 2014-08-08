#ifndef KRAKEN_EXCEPTION
#define KRAKEN_EXCEPTION

#include <exception>
#include <string>

namespace kraken {

class exception : public std::exception {

   public :

   exception();
   exception(std::string const&);

   char const* what() const throw();

   private :

   std::string message_;
};

}

#endif
