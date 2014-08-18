#include <gl_config.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>

#include <exception.hpp>
#include <particle_emitter.hpp>

namespace kraken {

gl_config::
   
gl_config(std::string const& shader_path) :
shader_path_(shader_path),
particle_number_(0),
rotation_(std::array<float,2>{{0.0f,0.0f}}),
depth_(-30.0f)
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

   const char * shader_source = load_shader(name,type).c_str();

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

   /*for(auto stage  = shader_store_.begin() ; 
            stage != shader_store_.end()   ; ++stage) {

      const char * shader_source(load_shader(stage->first,stage->second.type_));

      glShaderSource(stage->second.id_,1,&shader_source,nullptr);
      delete[] shader_source;

      glCompileShader(stage->second.id_);
      compile_feedback(stage->first);
   }

   std::cout << std::endl << "reloaded all shader" << std::endl;*/
}


void gl_config::load_default(vector_field const& vf) {

   particle_emitter emitter;
   
   particles pos(emitter.raster(10,vf.dim_));

   particle_number_ = pos.size_ / (3 * sizeof(float));

   GLuint vbo,vao;

   glGenBuffers(1,&vbo);
   glGenVertexArrays(1,&vao);

   glBindBuffer(GL_ARRAY_BUFFER,vbo);
   glBufferData(GL_ARRAY_BUFFER,pos.size_,pos.data_,GL_STATIC_DRAW);
   glBindVertexArray(vao);

   GLuint program_id(program_store_.find("triangle")->second);

   GLint attr_pos(glGetAttribLocation(program_id,"pos"));
   
   glEnableVertexAttribArray(attr_pos);
   glVertexAttribPointer(attr_pos,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,0);

   glm::mat4 perspective = 
   glm::perspective(45.0f,aspect_ratio_,0.1f,100.0f);

   GLint uniform_loc = glGetUniformLocation(program_id,"projection");
   glUniformMatrix4fv(uniform_loc,1,GL_FALSE,glm::value_ptr(perspective));

   glm::mat4 view;

   view[3][2] = depth_;

   uniform_loc = glGetUniformLocation(program_id,"view");
   glUniformMatrix4fv(uniform_loc,1,GL_FALSE,glm::value_ptr(view));

   glm::vec3 lightpos(0.0,0.0,5.0);
   uniform_loc = glGetUniformLocation(program_id,"lightpos");
   glUniform3fv(uniform_loc,1,glm::value_ptr(lightpos));

   glm::ivec3 dim(vf.dim_[0],vf.dim_[1],vf.dim_[2]);
   uniform_loc = glGetUniformLocation(program_id,"dim");
   glUniform3iv(uniform_loc,1,glm::value_ptr(dim));

   glm::vec2 interval(vf.min_,vf.max_);
   uniform_loc = glGetUniformLocation(program_id,"interval");
   glUniform2fv(uniform_loc,1,glm::value_ptr(interval));

   float border_color[] = {0.0f,0.0f,0.0f,1.0f};
 
   GLuint tex_id;
   glGenTextures(1, &tex_id);
   glEnable(GL_TEXTURE_3D);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_3D, tex_id);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
   glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
   glTexParameterfv(GL_TEXTURE_3D, GL_TEXTURE_BORDER_COLOR, border_color);
   glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB32F, 
                vf.dim_[0], vf.dim_[1], vf.dim_[2], 0, GL_RGB, 
                GL_FLOAT, vf.data_);
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


std::string const gl_config::load_shader(std::string const& name,GLenum type) const {

   std::string path(shader_path_) , buffer;

   if(path.back() != '/') path.append("/");

   path.append(name);
   path.append(shader_suffix(type));

   std::ifstream input(path);

   if(!input) throw exception("shader file : " + path + " doesn't exist");

   while(input.good()) {

      buffer.push_back(input.get());
   }

   input.close();

   buffer.pop_back();

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


void gl_config::rotate(bool axis,bool dir) {

   // x-axis left
   if     (axis &&  dir) rotation_[0] -= 0.02;

   // x-axis right
   else if(axis &&  !dir) rotation_[0] += 0.02;

  // y-axis left
   else if(!axis && !dir) rotation_[1] -= 0.02;

   // y-axis right
   else if(!axis && dir) rotation_[1] += 0.02;
}


void gl_config::zoom(bool in) {

   float increment(0.5f);

   // zoom out
   if(!in) increment = -increment;

   depth_ += increment;
}


void gl_config::load_model() {

   glm::mat4 view(glm::rotate(glm::mat4(),rotation_[0],glm::vec3(1.0,0.0,0.0)));

   view *= glm::rotate(glm::mat4(),rotation_[1],glm::vec3(0.0,1.0,0.0));

   view[3][2] = depth_;


   for(auto program  = program_store_.begin() ;
            program != program_store_.end()   ; ++program) {

      GLint uniform_loc = glGetUniformLocation(program->second,"view");
      glUniformMatrix4fv(uniform_loc,1,GL_FALSE,glm::value_ptr(view));
   }
}


void gl_config::load_projection() {

   for(auto program  = program_store_.begin() ;
            program != program_store_.end()   ; ++program) {

      glm::mat4 perspective = glm::perspective(45.0f,aspect_ratio_,0.1f,100.0f);

      GLint uniform_loc = glGetUniformLocation(program->second,"projection");
      glUniformMatrix4fv(uniform_loc,1,GL_FALSE,glm::value_ptr(perspective));
   }
}


unsigned gl_config::particle_number() const {

   return particle_number_;
}


void gl_config::aspect_ratio(std::array<unsigned short,2> const& res) {

   glViewport(0,0,res[0],res[1]);

   aspect_ratio_ = static_cast<float> (res[0]) / res[1];
}

}
