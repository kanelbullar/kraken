#include <fstream>
#include <iostream>

#include <config.hpp>

namespace kraken {

void config::enable_program(std::string const& name) {

   if(program_store_.find(name) == program_store_.end()) {

      std::cerr << "Couldn't enable program " << name
                << ", because the program don't exists in the database."
                << std::endl;
   }

   else {

      link_program(name);
   }
}


void config::add_program(std::string const& name) {

   if(program_store_.find(name) != program_store_.end()) {

      std::cerr << "Couldn't add program " << name 
                << ", because it already exists in the database."
                << std::endl;
   }

   else {

      GLuint program_id(glCreateProgram());

      program_store_.emplace(name,program_id);
   }
}


void config::

add_stage(std::string const& program_name,std::string const& stage_path) {

   if(program_store_.find(program_name) == program_store_.end()) {

      std::cerr << "Couldn't add stage " << stage_path
                << " to program "        << program_name
                << ", because the program don't exists in the database."
                << std::endl;
   }

   else {

      GLuint program_id(program_store_.find(program_name)->second);
      GLenum type(stage_type(stage_path));

      std::map<GLuint,std::string>::const_iterator stage;

      switch(type) {

         case GL_VERTEX_SHADER :

         stage = vertex_stage_.find(program_id);

         if(stage == vertex_stage_.end()) {
         
            vertex_stage_.emplace(program_id,stage_path);
         }

         else {

            std::cerr << "Couldn't add stage " << stage_path
                      << ", because the vertex stage " <<  stage->second
                      << " already exists in the database."
                      << std::endl;
         }

         break;

         case GL_GEOMETRY_SHADER :

         stage = geometry_stage_.find(program_id);

         if(stage == geometry_stage_.end()) {
         
            geometry_stage_.emplace(program_id,stage_path);
         }

         else {

            std::cerr << "Couldn't add stage " << stage_path
                      << ", because the geometry stage " <<  stage->second
                      << " already exists in the database."
                      << std::endl;
         }

         break;

         case GL_FRAGMENT_SHADER :

         stage = fragment_stage_.find(program_id);

         if(stage == fragment_stage_.end()) {
         
            fragment_stage_.emplace(program_id,stage_path);
         }

         else {

            std::cerr << "Couldn't add stage " << stage_path
                      << ", because the fragment stage " <<  stage->second
                      << " already exists in the database."
                      << std::endl;
         }

         break;

         default :

         std::cerr << "Couldn't add stage " << stage_path
                   << ", because the stage has an invalid suffix."
                   << " Valid Suffixes are .vert, .geom, .frag."
                   << std::endl;

         break;
      }
   }
}


void config::link_program(std::string const& name) {

   GLuint id(program_store_.find(name)->second);


   std::map<GLuint,std::string>::iterator stage(vertex_stage_.find(id));

   if(stage == vertex_stage_.end()) {

      std::cerr << "Couldn't enable program " << name
                << ", because no linked vertex stage exists."
                << std::endl;
   }

   else {

      GLuint shader_id(glCreateShader(stage_type(stage->second)));

      const char * source(load_file(stage->second));

      if(source == nullptr) {

         std::cerr << "Couldn't enable program " << name
                   << ", because the vertex stage file " << stage->second
                   << " is damaged or doesn't exist."
                   << std::endl;

         vertex_stage_.erase(stage);          
      }

      else {

         glShaderSource(shader_id,1,&source,nullptr);
         glCompileShader(shader_id);

         if(compile_feedback(shader_id,stage->second)) {

            glAttachShader(id,shader_id);
         }

         glDeleteShader(shader_id);
         delete[] source;
      }
   }

 
   stage = geometry_stage_.find(id);

   if(stage != geometry_stage_.end()) {

      GLuint shader_id(glCreateShader(stage_type(stage->second)));

      const char * source(load_file(stage->second));

      if(source == nullptr) {

         std::cerr << "Couldn't enable program " << name
                   << ", because the geometry stage file " << stage->second
                   << " is damaged or doesn't exist."
                   << std::endl;

         geometry_stage_.erase(stage);          
      }

      else {

         glShaderSource(shader_id,1,&source,nullptr);
         glCompileShader(shader_id);

         if(compile_feedback(shader_id,stage->second)) {

            glAttachShader(id,shader_id);
         }

         glDeleteShader(shader_id);
         delete[] source;
      }
   }


   stage = fragment_stage_.find(id);

   if(stage == fragment_stage_.end()) {

      std::cerr << "Couldn't enable program " << name
                << ", because no linked fragment stage exists."
                << std::endl;
   }

   else {

      GLuint shader_id(glCreateShader(stage_type(stage->second)));

      const char * source(load_file(stage->second));

      if(source == nullptr) {

         std::cerr << "Couldn't enable program " << name
                   << ", because the fragment stage file " << stage->second
                   << " is damaged or doesn't exist."
                   << std::endl;

         fragment_stage_.erase(stage);          
      }

      else {

         glShaderSource(shader_id,1,&source,nullptr);
         glCompileShader(shader_id);

         if(compile_feedback(shader_id,stage->second)) {

            glAttachShader(id,shader_id);
         }

         glDeleteShader(shader_id);
         delete[] source;
      }
   }


   glLinkProgram(id);
}


bool config::compile_feedback(GLuint shader_id,std::string const& path) const {

   GLint status;

   glGetShaderiv(shader_id,GL_COMPILE_STATUS,&status);

   if(status != GL_TRUE) {

      GLint   length(0);
      GLchar* info_buffer(nullptr);

      glGetShaderiv(shader_id,GL_INFO_LOG_LENGTH,&length);

      info_buffer = new GLchar[length];

      glGetShaderInfoLog(shader_id,length,nullptr,info_buffer);

      std::cerr << "stage: " << path
                << std::endl
                << " line: " << info_buffer
                << std::endl;

      delete[] info_buffer;

      return false;
   }

   return true;
}


bool config::link_feedback(std::string const& name) const {

   GLuint id(program_store_.find(name)->second);

   GLint link_status;

   glGetProgramiv(id,GL_LINK_STATUS,&link_status);

   if(link_status == GL_FALSE) {

      GLint   length(0);
      GLchar* info_buffer(nullptr);

      glGetProgramiv(id,GL_INFO_LOG_LENGTH,&length);

      info_buffer = new char[length];

      glGetProgramInfoLog(id,length,&length,info_buffer);

      std::cerr << std::endl
                << "program:" << name 
                << std::endl
                << "link error:" << info_buffer
                << std::endl;

      delete[] info_buffer;

      return false;
   }

   return true;
}


GLenum config::stage_type(std::string const& path) const {

   int suffix_pos(path.rfind('.'));

   if(suffix_pos == std::string::npos) return GL_INVALID_ENUM;

   unsigned short suffix_length(path.size()-suffix_pos-1);

   std::string suffix(path.substr(suffix_pos,suffix_length));


   if     (suffix == ".vert") return GL_VERTEX_SHADER;

   else if(suffix == ".geom") return GL_GEOMETRY_SHADER;

   else if(suffix == ".frag") return GL_FRAGMENT_SHADER;

   else                       return GL_INVALID_ENUM;
}


char* config::load_file(std::string const& path) const {

   char* buffer(nullptr);
   std::ifstream input(path);

   if(input) {

      int size(0);

      input.seekg(0,input.end);
      size = input.tellg();
      input.seekg(0,input.beg);
      buffer = new char[size];

      unsigned short index(0);

      while(input.good()) {

         buffer[index] = input.get();
         ++index;
      }

      input.close();
   }

   return buffer;
} 

}
