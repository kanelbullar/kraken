#include <vector_field.hpp>

namespace kraken {

   vector_field::
   
   vector_field(std::array<unsigned short,3> const& dim, GLvoid* data) :
   dim_(dim),
   data_(data)   
   {}


   vector_field::

   ~vector_field() {

      GLfloat* data = reinterpret_cast<GLfloat*> (data_);

      delete data;
   }
}
