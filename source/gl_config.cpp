#include <gl_config.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>

#include <exception.hpp>

namespace kraken {

   gl_config::
   
   gl_config(std::string const& shader_path) :
   shader_path_(shader_path)
   {}


   void gl_config::

   enable_program(std::string const& name) const {

      auto program(program_store_.find(name));

      if(program == program_store_.end()) {

         std::string message("unknown program : ");
         message.append(name);
         throw exception(message);
      }

      glUseProgram(program->second);
   }


   void gl_config::

   add_shader(std::string const& name,GLenum type) {

      if(!valid_stage(type)) {

         throw(exception("invalid shader type"));
      }

      const char * shader_source(load_shader(name,type));

      GLuint shader_id(glCreateShader(type));

      glShaderSource(shader_id,1,&shader_source,nullptr);

      shader_store_.emplace(name,shader_stage(shader_id,type));
   }


   void gl_config::

   add_program(std::string const& name,
               std::array<std::string,3> const& stages) {

      
      std::array<bool,3> complete;

      complete.fill(false);

      GLuint program_id(glCreateProgram());

      for(unsigned short index = 0 ; index < stages.size() ; ++index) {

         auto stage(shader_store_.find(stages[index]));

         if(stage == shader_store_.end()) {

            std::string message("unknown shader stage : ");
            message.append(stages[index]);
            throw exception(message);
         }

         switch(stage->second.type_) {

            case GL_VERTEX_SHADER   : complete[0] = true; break;

            case GL_GEOMETRY_SHADER : complete[1] = true; break;
            
            case GL_FRAGMENT_SHADER : complete[2] = true; break;
         }

         glCompileShader(stage->second.id_);
         compile_feedback(stages[index]);
         glAttachShader(program_id,stage->second.id_);
      }

      if(std::all_of(complete.begin(),complete.end(),

         [](bool gl_s){return gl_s;})) {

         glLinkProgram(program_id);
         program_store_.emplace(name,program_id);
      }

      else {

         throw exception("shading pipeline incomplete");
      }
   }


   void gl_config::reload_shader() const {

      for(auto stage  = shader_store_.begin() ; 
               stage != shader_store_.end()    ; ++stage) {

         const char * shader_source(load_shader(stage->first,
                                                stage->second.type_));

         glShaderSource(stage->second.id_,1,&shader_source,nullptr);

         glCompileShader(stage->second.id_);
         compile_feedback(stage->first);
         
      }

      std::cout << std::endl << "reloaded all shader" << std::endl;
   }


   bool gl_config::valid_stage(GLenum type) const {

      if(type != GL_VERTEX_SHADER   &&
         type != GL_GEOMETRY_SHADER &&
         type != GL_FRAGMENT_SHADER   )

         return false;

      else

         return true;
   }


   char* gl_config::load_shader(std::string const& name,GLenum type) const {

      std::string path(shader_path_);

      if(path.back() != '/') path.append("/");

      path.append(name);
      path.append(shader_suffix(type));

      std::ifstream input(path);

      if(!input) throw exception("shader file : " + path + " doesn't exist");

      std::filebuf* buffer_ptr(input.rdbuf());

      std::size_t size(buffer_ptr->pubseekoff(0,input.end,input.in));

      buffer_ptr->pubseekpos(0,input.in);

      char* buffer(new char[size]);
      
      buffer_ptr->sgetn(buffer,size);   

      input.close();

      return buffer;
   }


   std::string const gl_config::

   shader_suffix(GLenum type) const {

      std::string suffix(".");

      switch(type) {

         case GL_VERTEX_SHADER   : suffix.append("vert"); break;

         case GL_GEOMETRY_SHADER : suffix.append("geom"); break;

         case GL_FRAGMENT_SHADER : suffix.append("frag"); break;

         default : throw exception("invalid shader type");
      }

      return suffix;
   }


   void gl_config::

   compile_feedback(std::string const& name) const {

      auto stage(shader_store_.find(name));

      GLint status;

      glGetShaderiv(stage->second.id_,GL_COMPILE_STATUS,&status);

      if(status != GL_TRUE) {

         GLint   length;
         GLchar* info_buffer;

         glGetShaderiv(stage->second.id_,GL_INFO_LOG_LENGTH,&length);

         info_buffer = new GLchar[length];

         glGetShaderInfoLog(stage->second.id_,length,nullptr,info_buffer);

         std::cerr << std::endl 
                   << "shader:" << name << shader_suffix(stage->second.type_)
                   << " line: " << info_buffer
                   << std::endl;

         delete[] info_buffer;
      }      
   }
}
