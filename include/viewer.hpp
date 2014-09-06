#ifndef KRAKEN_VIEWER
#define KRAKEN_VIEWER

#include <config.hpp>
#include <vector_field.hpp>

namespace kraken {

  class viewer {

    public :

    viewer(unsigned short,unsigned short);

    void open(vector_field const&, transfer_function const&);
    void init(int,char**) const;


    private :

    int handle_;

    std::array<unsigned short,2> res_;
  };
}

#endif
