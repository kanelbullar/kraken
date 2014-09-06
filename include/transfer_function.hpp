#ifndef KRAKEN_TRANSFER_FUNCTION
#define KRAKEN_TRANSFER_FUNCTION

#include <vector>
#include <array>
#include <algorithm>
#include <iostream>

namespace kraken {
typedef std::array<float,4> rgba;

struct control_point {

   control_point(float,rgba const&);

   bool operator < (control_point const&) const;

   /*inline control_point& operator= (control_point const& cp)  {
      position = cp.position;
      color    = cp.color;
      return *this;
   }*/

   float position;
   rgba color;
};

/*inline bool operator < (control_point const& cp1, control_point const& cp2) {
   return cp1 < cp2;
}*/


class transfer_function {

   public:

   transfer_function();
   ~transfer_function();
   void add (float, rgba);
   float* finish () const; 
   unsigned short resolution() const;

   private:

   void sort() const;

   control_point left_calc(float) const;
   control_point right_calc(float) const;
   unsigned short resolution_;
   mutable std::vector <control_point> control_points_;
};

}

#endif
