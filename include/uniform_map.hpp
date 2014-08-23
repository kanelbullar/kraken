#ifndef UNIFORM_MAP_HPP
#define UNIFORM_MAP_HPP

#include <map>
#include <memory>
#include <string>

#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <glm/glm.hpp>


struct uniform_link
{
  inline uniform_link(GLuint id,std::string const& name) :
  program_id_(id),
  uniform_name_(name)
  {}

  GLuint program_id_;

  std::string uniform_name_;
};


enum uniform_type {VEC2,VEC3,IVEC3,MAT4};


class uniform_map
{
  public :

  void load(uniform_link const&) const;

  void set(std::string const&,glm::vec2 const&);
  void set(std::string const&,glm::vec3 const&);
  void set(std::string const&,glm::ivec3 const&);
  void set(std::string const&,glm::mat4 const&);

  bool aviable(std::string const&) const;


  private :

  std::shared_ptr<unsigned short> const id(std::string const&);


  std::map<std::string,std::shared_ptr<unsigned short> > names_;
  std::map<std::shared_ptr<unsigned short>,uniform_type> types_;

  std::map<std::shared_ptr<unsigned short>,glm::vec2>    vec2_;
  std::map<std::shared_ptr<unsigned short>,glm::vec3>    vec3_;
  std::map<std::shared_ptr<unsigned short>,glm::ivec3>   ivec3_;
  std::map<std::shared_ptr<unsigned short>,glm::mat4>    mat4_;
};

#endif
