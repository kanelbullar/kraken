#include <transfer_function.hpp>

namespace kraken {
   transfer_function::transfer_function():
   resolution_(100) { }
   
   transfer_function::~transfer_function() { }
   
   void transfer_function::add (float pos, rgba val) {
      if(pos >= 0.0 && pos <= 1.0) {
         control_point cp (pos,val);
         control_points_.insert(cp);
      }
   }
   
   void transfer_function::finish () {
      
      //float* data = new float [resolution_ * 4];

      for(int i = 0; i <= resolution_; ++i) {
         //float position = static_cast<float> (i)/resolution_;
         //control_point left = left(position);
         //control_point right = right(position); 
      }
   }

   control_point transfer_function::left(float position) {
      for(auto it = control_points_.end(); it != control_points_.begin(); --it){
         if (it->position <= position) return *it;
      }
      return control_point(0.0,std::array<float,4>{{0.0,0.0,0.0,0.0}});;
   }

   control_point transfer_function::right(float position) {
      for(auto it = control_points_.begin(); it != control_points_.end(); ++it){
         if (it->position >= position) return *it;
      }
      return control_point(1.0,std::array<float,4>{{0.0,0.0,0.0,0.0}});;
   }
}
