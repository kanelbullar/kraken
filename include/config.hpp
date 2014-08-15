#ifndef KRAKEN_CONFIG
#define KRAKEN_CONFIG

#include <map>

#include <GL/glew.h>

namespace kraken {

class config {

   public :

   void enable_program(std::string const&);
   void add_program(std::string const&);
   void add_stage(std::string const&,std::string const&);

   private :

   void link_program(std::string const&);
   bool compile_feedback(GLuint shader_id,std::string const&) const;
   bool link_feedback(std::string const&) const;
   GLenum stage_type(std::string const&) const;

   char* load_file(std::string const&) const;

   std::map<std::string,GLuint> program_store_;
   std::map<GLuint,std::string> vertex_stage_;
   std::map<GLuint,std::string> geometry_stage_;
   std::map<GLuint,std::string> fragment_stage_;
};

}

#endif
