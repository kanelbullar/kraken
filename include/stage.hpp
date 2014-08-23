#ifndef STAGE_HPP
#define STAGE_HPP

#include <string>

#include <GL/glew.h>


class stage
{
  public :

  stage(std::string const&);

  ~stage();

  GLuint compile();

  bool equal(std::string const&) const;

  GLuint id() const;

  GLenum type() const;

  void clear();


  private :

  const GLchar* const load() const;

  bool compile_feedback() const;

  GLenum recognize_type() const;


  GLuint id_;

  GLenum type_;

  std::string path_;
};

#endif
