#include <gl_config.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>

#include <exception.hpp>

namespace kraken {

gl_config::
   
gl_config(std::string const& shader_path) :
shader_path_(shader_path)
{}


void gl_config::enable_program(std::string const& name) const {

   auto program(program_store_.find(name));

   if(program == program_store_.end()) {

      std::string message("unknown program : ");
      message.append(name);
      throw exception(message);
   }

   glUseProgram(program->second);
}


void gl_config::add_shader(std::string const& name,GLenum type) {

   if(!valid_stage(type)) throw(exception("invalid shader type"));

   const char * shader_source(load_shader(name,type));

   GLuint shader_id(glCreateShader(type));

   glShaderSource(shader_id,1,&shader_source,nullptr);

   shader_store_.emplace(name,shader_stage(shader_id,type));
}


void gl_config::add_program(std::string const& name,
                            std::array<std::string,3> const& stages) {

   std::array<bool,3> complete;
   std::array<GLuint,3> linked_shader;

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
      linked_shader[index] = stage->second.id_;
   }

   if(std::all_of(complete.begin(),
                  complete.end(),
                  [](bool gl_s){return gl_s;})) {

      glLinkProgram(program_id);

      link_.emplace(program_id,linked_shader);
      program_store_.emplace(name,program_id);
      link_feedback(name);
      clean(program_id);
   }

   else throw exception("shading pipeline incomplete");
}


void gl_config::reload_shader() const {

   /*for(auto link(link_.begin() ; link != link_.end() ; ++link)) {

      auto stages(link->second);

      for(auto stage(stages.begin()) ; stage != stages.end() ; ++stage) {

         const char* stage_source();
      }
   }*/

   for(auto stage  = shader_store_.begin() ; 
            stage != shader_store_.end()   ; ++stage) {

      const char * shader_source(load_shader(stage->first,stage->second.type_));

      glShaderSource(stage->second.id_,1,&shader_source,nullptr);
      delete[] shader_source;

      glCompileShader(stage->second.id_);
      compile_feedback(stage->first);
   }

   std::cout << std::endl << "reloaded all shader" << std::endl;
}


void gl_config::load_default() {

   GLfloat pos[] = {0.0,0.0,0.0};

   GLuint vbo,vao;

   glGenBuffers(1,&vbo);
   glGenVertexArrays(1,&vao);

   glBindBuffer(GL_ARRAY_BUFFER,vbo);
   glBufferData(GL_ARRAY_BUFFER,sizeof(pos),pos,GL_STATIC_DRAW);
   glBindVertexArray(vao);

   GLuint program_id(program_store_.find("triangle")->second);

   GLint attr_pos(glGetAttribLocation(program_id,"pos"));
   
   glEnableVertexAttribArray(attr_pos);
   glVertexAttribPointer(attr_pos,3,GL_FLOAT,GL_FALSE,0,0);

   glm::mat4 perspective = 
   glm::perspective(45.0f,static_cast<float> (1000) / 800,0.1f,100.0f);

   GLint uniform_loc = glGetUniformLocation(program_id,"projection");
   glUniformMatrix4fv(uniform_loc,1,GL_FALSE,glm::value_ptr(perspective));

   glm::mat4 view = glm::mat4(glm::vec4(1.0f,0.0f,0.0f,0.0f),
                              glm::vec4(0.0f,1.0f,0.0f,0.0f),
                              glm::vec4(0.0f,0.0f,1.0f,0.0f),
                              glm::vec4(0.0f,0.0f,-15.0f,1.0f));

   uniform_loc = glGetUniformLocation(program_id,"view");
   glUniformMatrix4fv(uniform_loc,1,GL_FALSE,glm::value_ptr(view));

   glm::vec3 lightpos(0.0,0.0,5.0);
   uniform_loc = glGetUniformLocation(program_id,"lightpos");
   glUniform3fv(uniform_loc,1,glm::value_ptr(lightpos));
}


void gl_config::clean(GLuint program_id) const {

   auto linked_shader(link_.find(program_id)->second);

   for(auto stage(linked_shader.begin()) ;
       stage != linked_shader.end()      ; ++stage) {

      glDetachShader(program_id,*(stage));
      //glDeleteShader(*(stage));
   }
}


bool gl_config::valid_stage(GLenum type) const {

   if(type != GL_VERTEX_SHADER   &&
      type != GL_GEOMETRY_SHADER &&
      type != GL_FRAGMENT_SHADER   )  return false;

   return true;   
}


char* gl_config::load_shader(std::string const& name,GLenum type) const {

   std::string path(shader_path_);

   if(path.back() != '/') path.append("/");

   path.append(name);
   path.append(shader_suffix(type));

   std::ifstream input(path);

   if(!input) throw exception("shader file : " + path + " doesn't exist");

   int size(0),index(0);
   char* buffer(nullptr);

   input.seekg(0,input.end);
   size = input.tellg();
   input.seekg(0,input.beg);

   buffer = new char[size];

   while(input.good()) {

      buffer[index] = input.get();
      ++index;
   }

   input.close();
   
   std::cout<<buffer;

   return buffer;
} 


std::string const gl_config::shader_suffix(GLenum type) const {

   std::string suffix(".");

   switch(type) {

      case GL_VERTEX_SHADER   : suffix.append("vert"); break;

      case GL_GEOMETRY_SHADER : suffix.append("geom"); break;

      case GL_FRAGMENT_SHADER : suffix.append("frag"); break;

      default : throw exception("invalid shader type");
   }

   return suffix;
}


void gl_config::compile_feedback(std::string const& name) const {

   auto stage(shader_store_.find(name));

   GLint status;

   glGetShaderiv(stage->second.id_,GL_COMPILE_STATUS,&status);

   if(status != GL_TRUE) {

      GLint   length(0);
      GLchar* info_buffer(nullptr);

      glGetShaderiv(stage->second.id_,GL_INFO_LOG_LENGTH,&length);

      info_buffer = new GLchar[length];

      glGetShaderInfoLog(stage->second.id_,length,nullptr,info_buffer);

      std::cerr << std::endl 
                << "shader:" << name << shader_suffix(stage->second.type_)
                << std::endl
                << " line: " << info_buffer
                << std::endl;

      delete[] info_buffer;
   }      
}


void gl_config::link_feedback(std::string const& program_name) const {

   auto program(program_store_.find(program_name));

   GLint link_status;

   glGetProgramiv(program->second,GL_LINK_STATUS,&link_status);

   if(link_status == GL_FALSE) {

      GLint   length(0);
      GLchar* info_buffer(nullptr);

      glGetProgramiv(program->second,GL_INFO_LOG_LENGTH,&length);

      info_buffer = new char[length];

      glGetProgramInfoLog(program->second,length,&length,info_buffer);

      std::cerr << std::endl
                << "program:" << program_name 
                << std::endl
                << "link error:" << info_buffer
                << std::endl;

      delete[] info_buffer;
   }
}

}
