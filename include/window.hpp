#ifndef KRAKEN_WINDOW
#define KRAKEN_WINDOW

#include <array>
#include <string>

#include <exception.hpp>
#include <pipeline.hpp>

namespace kraken {

class window {

   public:

   window(unsigned short,unsigned short);
   ~window();

   void open(int,char**);

   private:

   std::array<unsigned short,2> res_;
   std::string                  title_;
   int                          handle_;
};

}

#endif
