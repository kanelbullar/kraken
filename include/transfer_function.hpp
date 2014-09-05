#ifndef KRAKEN_TRANSFER_FUNCTION
#define KRAKEN_TRANSFER_FUNCTION

#include <set>
#include <array>
#include <random>
#include <iostream>

namespace kraken {
typedef std::array<float,4> rgba;

struct control_point {
   inline control_point(float pos,rgba col):position(pos),
                                            color(col) {}
   float position;
   rgba color;

   inline bool operator < (control_point const& cp) {
      return this->position < cp.position;
   }

   inline bool operator > (control_point const& cp) {
      return position > cp.position;
   }

   inline bool operator == (control_point const& cp) {
      return position == cp.position;
   }
};

inline bool operator < (control_point const& cp1, control_point const& cp2) {
   return cp1 < cp2;
}

inline bool operator > (control_point const& cp1, control_point const& cp2) {
   return cp1 > cp2;
}

inline bool operator == (control_point const& cp1, control_point const& cp2) {
   return cp1 == cp2;
}


class transfer_function {

   public:

   transfer_function();
   ~transfer_function();
   void add (float, rgba);
   void finish (); 

   private:

   control_point left(float);
   control_point right(float);
   unsigned short resolution_;
   std::set <control_point> control_points_;
};

}

#endif
