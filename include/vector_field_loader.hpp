#ifndef KRAKEN_VECTOR_FIELD_LOADER
#define KRAKEN_VECTOR_FIELD_LOADER

#include <vector_field.hpp>
#include <iostream>
#include <progress.hpp>

namespace kraken {

class vector_field_loader {

   public :
   vector_field_loader();
   vector_field const load(std::string const&, 
                           std::array<unsigned short,3> const&);

   private :
   std::array<float,2> const min_max (unsigned long) const;
   float* data_;

};

}

#endif
