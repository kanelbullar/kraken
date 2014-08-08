#include <exception.hpp>

namespace kraken {

   exception::exception() :
   message_(std::string("undefined exception"))
   {}

   exception::exception(std::string const& message) :
   message_(message)
   {}

   char const* exception::what() const throw()
   {
      return message_.c_str();
   }

}
