#include <uniform_map.hpp>

#include <iostream>

#include <glm/gtc/type_ptr.hpp>


void uniform_map::

load(uniform_link const& ul) const
{
  GLuint program_id(ul.program_id_);

  std::string uniform_name(ul.uniform_name_);

  auto name_it(names_.find(uniform_name));

  if(name_it != names_.end())
  {
    GLint uniform_loc(glGetUniformLocation(program_id,uniform_name.c_str()));

    if(uniform_loc != -1)
    {
      auto type_it(types_.find(name_it->second));

      switch(type_it->second)
      {
        case VEC2 :
        {
          glm::vec2 vec2_uf(vec2_.find(name_it->second)->second);
          glUniform2fv(uniform_loc,1,glm::value_ptr(vec2_uf));
          break;
        }

        case VEC3 :
        {
          glm::vec3 vec3_uf(vec3_.find(name_it->second)->second);
          glUniform3fv(uniform_loc,1,glm::value_ptr(vec3_uf));
          break;
        }

        case IVEC3 :
        {
          glm::ivec3 ivec3_uf(ivec3_.find(name_it->second)->second);
          glUniform3iv(uniform_loc,1,glm::value_ptr(ivec3_uf));
          break;
        }

        case MAT4 :
        {
          glm::mat4 mat4_uf(mat4_.find(name_it->second)->second);
          glUniformMatrix4fv(uniform_loc,1,GL_FALSE,glm::value_ptr(mat4_uf));
          break;
        }
      }
    }

    else
    {
      std::cerr << std::endl
                << "uniform [" << uniform_name << "] isn't bound"
                << std::endl;
    }
  }

  else
  {
    std::cerr << std::endl
              << "uniform [" << uniform_name << "] isn't aviable"
              << std::endl;
  }
}


void uniform_map::

set(std::string const& name , glm::vec2 const& uniform)
{
  std::shared_ptr<unsigned short> key(id(name));

  auto uniform_it(vec2_.find(key));

  if(uniform_it == vec2_.end())
  {
    if(types_.find(key) == types_.end())
    {
      vec2_.emplace(key,uniform);

      types_.emplace(key,VEC2);
    }

    else
    {
      std::cerr << std::endl
                << "uniform [" << name << "] is already bound"
                << std::endl;
    }
  }

  else
  {
    uniform_it->second = uniform;
  }
}


void uniform_map::

set(std::string const& name , glm::vec3 const& uniform)
{
  std::shared_ptr<unsigned short> key(id(name));

  auto uniform_it(vec3_.find(key));

  if(uniform_it == vec3_.end())
  {
    if(types_.find(key) == types_.end())
    {
      vec3_.emplace(key,uniform);

      types_.emplace(key,VEC3);
    }

    else
    {
      std::cerr << std::endl
                << "uniform [" << name << "] is already bound"
                << std::endl;
    }
  }

  else
  {
    uniform_it->second = uniform;
  }
}


void uniform_map::

set(std::string const& name , glm::ivec3 const& uniform)
{
  std::shared_ptr<unsigned short> key(id(name));

  auto uniform_it(ivec3_.find(key));

  if(uniform_it == ivec3_.end())
  {
    if(types_.find(key) == types_.end())
    {
      ivec3_.emplace(key,uniform);

      types_.emplace(key,IVEC3);
    }

    else
    {
      std::cerr << std::endl
                << "uniform [" << name << "] is already bound"
                << std::endl;
    }
  }

  else
  {
    uniform_it->second = uniform;
  }
}


void uniform_map::

set(std::string const& name , glm::mat4 const& uniform)
{
  std::shared_ptr<unsigned short> key(id(name));

  auto uniform_it(mat4_.find(key));

  if(uniform_it == mat4_.end())
  {
    if(types_.find(key) == types_.end())
    {
      mat4_.emplace(key,uniform);

      types_.emplace(key,MAT4);
    }

    else
    {
      std::cerr << std::endl
                << "uniform [" << name << "] is already bound"
                << std::endl;
    }
  }

  else
  {
    uniform_it->second = uniform;
  }
}


bool uniform_map::

aviable(std::string const& uniform_name) const
{
  auto name_it(names_.find(uniform_name));

  if(name_it != names_.end()) return true;

  return false;
}


std::shared_ptr<unsigned short> const uniform_map::

id(std::string const& name)
{
  std::shared_ptr<unsigned short> id_ptr;

  auto name_it(names_.find(name));

  if(name_it == names_.end())
  {
    id_ptr = std::make_shared<unsigned short>(names_.size());

    names_.emplace(name,id_ptr);
  }

  else
  {
    id_ptr = name_it->second;
  }

  return id_ptr;
}
