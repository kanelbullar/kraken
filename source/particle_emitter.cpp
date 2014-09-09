#include <particle_emitter.hpp>

namespace kraken {
   particle_emitter::particle_emitter() {}


   particle_emitter::~particle_emitter() {}


   particles const particle_emitter::raster(int number, vec3 const& dim) const {   
      float number_f = static_cast<float>(number);     

      std::vector<pos3> particle;
      
      for(float z = -(dim[2]/2); z < dim[2]/2; z+=dim[2]/number_f) {
         for(float y = -(dim[1]/2); y < dim[1]/2; y+=dim[1]/number_f) {
            for(float x = -(dim[0]/2); x < dim[0]/2; x+=dim[0]/number_f) {
              
               particle.push_back(pos3{{x,y,z}});
            }
         }
      }

      return convert(particle);
   }


   particles const particle_emitter::gauss(int number, vec3 const& dim) const {
      return particles(0,nullptr);
   }


   // TODO: Abfangen, dass Punkte nicht doppelt vergeben werden
   particles const particle_emitter::random(int number, vec3 const& dim) const {
      std::vector<pos3> particle;

      std::default_random_engine generator;
      std::uniform_real_distribution<float> x_dist(-(dim[0]/2),dim[0]/2);
      std::uniform_real_distribution<float> y_dist(-(dim[1]/2),dim[1]/2);
      std::uniform_real_distribution<float> z_dist(-(dim[2]/2),dim[2]/2);  

      for(int index = 0; index < number; ++index) {
         particle.push_back(pos3{{x_dist(generator),
                                  y_dist(generator),
                                  z_dist(generator)}});
      }
   
      return convert(particle);
   }


   particles const particle_emitter::cube(int number, 
                                          vec3 const& pos, 
                                          vec3 const& dim, 
                                          kraken::direction_type direction) {
      
      float number_f = static_cast<float>(number);

      std::vector<pos3> particle;

      switch (direction) {
         
         case FRONT:
            
            for(float y = pos[1]; y < pos[1] + dim[1]; y+=dim[1]/number_f) {
               for(float x = pos[0]; x < pos[0] + dim[0]; x+=dim[0]/number_f) {
                  particle.push_back(pos3{{x,y,static_cast<float>(pos[2])}});
               }
            }
            break;
              
         case BACK:

            for(float y = pos[1]; y < pos[1] + dim[1]; y+=dim[1]/number_f) {
               for(float x = pos[0]; x < pos[0] + dim[0]; x+=dim[0]/number_f) {
                  particle.push_back(pos3{{x,y,static_cast<float>(pos[2]+dim[2])}});
               }
            }
            break;

         case DOWN: 
   
            for(float z = pos[2]; z < pos[2] + dim[2]; z+=dim[2]/number_f) {
               for(float x = pos[0]; x < pos[0] + dim[0]; x+=dim[0]/number_f) {
                  particle.push_back(pos3{{x,static_cast<float>(pos[1]),z}});
               }
            }
            break;

         case UP:

            for(float z = pos[2]; z < pos[2] + dim[2]; z+=dim[2]/number_f) {
               for(float x = pos[0]; x < pos[0] + dim[0]; x+=dim[0]/number_f) {
                  particle.push_back(pos3{{x,static_cast<float>(pos[1]+dim[1]),z}});
               }
            }
            break;

         case LEFT:

            for(float z = pos[2]; z < pos[2] + dim[2]; z+=dim[2]/number_f) {
               for(float y = pos[1]; y < pos[1] + dim[1]; y+=dim[1]/number_f) {
                  particle.push_back(pos3{{static_cast<float>(pos[0]),y,z}});
               }
            }
            break;

         case RIGHT:    

            for(float z = pos[2]; z < pos[2] + dim[2]; z+=dim[2]/number_f) {
               for(float y = pos[1]; y < pos[1] + dim[1]; y+=dim[1]/number_f) {
                  particle.push_back(pos3{{static_cast<float>(pos[0]+dim[0]),y,z}});
               }
            }
            break;     

      }
      
      return convert(particle);
   }


   particles const particle_emitter::convert(std::vector<pos3> const& position) const {
      unsigned long size = position.size() * 3 , index = 0;     
      float* data = new float[size];      
      for(auto it = position.begin(); it != position.end(); ++it) {

         auto array = *it;
         data[index] = array[0];
         data[++index] = array[1];
         data[++index] = array[2];
         ++index;
      }

      return particles(size*sizeof(float),reinterpret_cast<void*>(data));
   }
}
