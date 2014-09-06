#include <transfer_function.hpp>
#include <iostream>

namespace kraken {

   control_point::control_point(float pos,rgba const& col):
   position(pos),
   color(col)
   {}

   bool control_point::operator < (control_point const& cp) const {
      return position < cp.position;
   }

   transfer_function::transfer_function():
   resolution_(100),control_points_(std::vector <control_point>()) { }
   
   transfer_function::~transfer_function() { }
   
   void transfer_function::add (float pos, rgba val) {
      if(pos >= 0.0 && pos <= 1.0) {

         control_point cp (pos,val);
         control_points_.push_back(cp);
      }
   }
   
   float* transfer_function::finish () const {
      
      sort();
      
      float* data = new float [resolution_ * 4];
      float position, distance, rel_pos, weight;

      for(int i = 0; i < resolution_; ++i) {

         position = static_cast<float> (i)/resolution_;
         control_point left = left_calc(position);
         control_point right = right_calc(position);
         
         distance = right.position - left.position;
         rel_pos = position - left.position;
         weight = rel_pos/distance;
         

         data[i*4]     = (1-weight)*left.color[0] + weight*right.color[0];
         data[(i*4+1)] = (1-weight)*left.color[1] + weight*right.color[1];
         data[(i*4+2)] = (1-weight)*left.color[2] + weight*right.color[2];
         data[(i*4+3)] = (1-weight)*left.color[3] + weight*right.color[3];

         //std::cout<<"r: "<<data[i*4]<<", g: "<<data[(i*4+1)]<<", b: "<<data[(i*4+2)]<<", a: "<<data[(i*4+3)]<<", left: "<<left.position<<", right: "<<right.position<<std::endl;
      }

      return data;
   }

   control_point transfer_function::left_calc(float position) const {
      for(auto it = control_points_.rbegin(); it != control_points_.rend(); ++it){
         if (it->position <= position) return *it;
      }
      return control_point(0.0,std::array<float,4>{{0.0,0.0,0.0,0.0}});;
   }

   control_point transfer_function::right_calc(float position) const {
      for(auto it = control_points_.begin(); it != control_points_.end(); ++it){
         if (it->position > position) return *it;
      }
      return control_point(1.0,std::array<float,4>{{0.0,0.0,0.0,0.0}});;
   }

   unsigned short transfer_function::resolution() const {
      return resolution_;
   }

   void transfer_function::sort() const {

      for(unsigned i = 0 ; i < control_points_.size() ; ++i) {

         for(unsigned j = 0 ; j < control_points_.size() - 1 ; ++j) {

            if(control_points_[j+1] < control_points_[j]) {

               control_point temp(control_points_[j]);

               control_points_[j]   = control_points_[j+1];
               control_points_[j+1] = temp;
            }
         }
      }
   }
}
