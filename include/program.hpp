#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <stage.hpp>

#include <array>
#include <memory>


class program
{
  public :

  program(std::string const&);

  ~program();

  void link();

  void reset_stage(GLenum);

  void define_stage(std::shared_ptr<stage> &);

  bool equal(std::string const&) const;

  GLuint id() const;


  private :

  void clear();

  void clear_stages() const;

  bool link_feedback() const;


  GLuint id_;

  std::string name_;

  std::array<std::shared_ptr<stage>,5> stages_;
};

#endif
