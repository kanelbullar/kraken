#ifndef KRAKEN_GL_CONFIG
#define KRAKEN_GL_CONFIG

#include <array>
#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector_field.hpp>

namespace kraken {

struct shader_stage {

   inline shader_stage(GLuint id,GLenum type) :
   id_(id),
   type_(type)
   {}

   GLuint id_;
   GLenum type_;
};

class gl_config {

   public :

   gl_config(std::string const& = "shader");

   void enable_program(std::string const&) const;
   void add_shader(std::string const&,GLenum);
   void add_program(std::string const&,std::array<std::string,3> const&);

   void reload_shader() const;

   void load_default(vector_field const&);

   void rotate(bool,bool);
   void zoom(bool);

   void load_model();
   void load_projection();

   unsigned particle_number() const;

   void aspect_ratio(std::array<unsigned short,2> const&);

   private :

   void clean(GLuint) const;

   std::string const load_shader(std::string const&,GLenum type) const;

   void  compile_feedback(std::string const&) const;
   void  link_feedback(std::string const&) const;

   bool  valid_stage(GLenum) const;
   std::string const shader_suffix(GLenum) const;


   std::string shader_path_;

   std::map<std::string,shader_stage>     shader_store_;
   std::map<GLuint,std::array<GLuint,3> > link_;
   std::map<std::string,GLuint>           program_store_;

   unsigned particle_number_;

   std::array<float,2> rotation_;

   float aspect_ratio_ , depth_;
};

}

#endif
