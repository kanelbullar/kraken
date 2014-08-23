#ifndef KRAKEN_VIEWER
#define KRAKEN_VIEWER

#include <vector_field.hpp>

#include <GL/freeglut.h>

namespace kraken {

  class viewer {

    public :

    viewer(unsigned short,unsigned short);

    void open() const;
    void init(int,char**) const;

    private :

    std::array<unsigned short,2> res_;
  };
}

#endif
