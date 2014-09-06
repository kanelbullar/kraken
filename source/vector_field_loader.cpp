#include <vector_field_loader.hpp>
#include <cmath>
#include <fstream>
#include <iostream>

namespace kraken {

vector_field_loader::vector_field_loader():data_(nullptr){}

vector_field const vector_field_loader::
load(std::string const& path, std::array<unsigned short,3> const& dim) {

     char* source(nullptr);

     std::ifstream input(path, std::ios::in | std::ios::binary);

     if(input.good()) {

       unsigned long length(0);

       input.seekg(0,input.end);
       length = input.tellg();
       input.seekg(0,input.beg);

       if(length != 0) {

         source = new char[length];

         input.get(source,length);

         if(input.gcount() != length - 1) {

           std::cerr << std::endl
                     << "failed to load " << path
                     << std::endl;

           delete[] source;

           source = nullptr;
         }
       }

       input.close();
     }

     else {

       std::cerr << std::endl
                 << "file " << path << " doesn't exist"
                 << std::endl;
     }

     data_ = reinterpret_cast<float*> (source);
     std::array<float,2> min_max_ = min_max(dim[0]*dim[1]*dim[2]);
     return vector_field(dim, data_, min_max_[0], min_max_[1]);
}

std::array<float,2> const vector_field_loader::
min_max (unsigned long size) const {  

   if (data_ == nullptr) return std::array<float,2>{{0.0,0.0}};

   float absolute, min, max;

   for(unsigned long index = 0 ; index < size ; ++index) {
      absolute = sqrt(pow(data_[index]  ,2) + 
                      pow(data_[index+1],2) + 
                      pow(data_[index+2],2));

      if(index == 0) {

         min = absolute;
         max = absolute;
      }

      if     (absolute < min) min = absolute;
      else if(absolute > max) max = absolute;
      
      index = index + 2;
   }

   return std::array<float,2>{{min,max}};
}

}
