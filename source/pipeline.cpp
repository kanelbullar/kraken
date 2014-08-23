#include <pipeline.hpp>

#include <iostream>


void pipeline::

enable(std::string const& program_name)
{
  program_iterator p_it(find_program(program_name));

  if(p_it != programs_.end())
  {
    if(p_it->id() != 0)
    {
      glUseProgram(p_it->id());

      for(auto l_it(links_.begin()) ; l_it != links_.end() ; ++l_it)
      {
        if(l_it->program_id_ == p_it->id()) uniforms_.load(*l_it);
      }
    }

    else
    {
      std::cerr << std::endl
                << "program [" << program_name << "] isn't linked"
                << std::endl;
    }    
  }

  else
  {
    std::cerr << std::endl
              << "program [" << program_name << "] doesn't exists"
              << std::endl;
  }
}


void pipeline::

add_program(std::string const& name)
{
  program_iterator p_it(find_program(name));

  if(p_it == programs_.end())
  {
    programs_.push_back(program(name));
  }

  else
  {
    std::cerr << std::endl
              << "program [" << name << "] already exists"
              << std::endl;
  }
}


void pipeline::

set_stage(std::string const& program_name , std::string const& stage_path)
{
  program_iterator p_it(find_program(program_name));

  if(p_it != programs_.end())
  {
    stage_iterator s_it(find_stage(stage_path));

    if(s_it == stages_.end())
    {
      std::shared_ptr<stage> s(std::make_shared<stage>(stage(stage_path)));

      stages_.push_back(s);

      p_it->define_stage(s);
    }

    else
    {
      p_it->define_stage(*s_it);
    }
  }

  else
  {
    std::cerr << std::endl
              << "program [" << program_name << "] doesn't exist"
              << std::endl;
  }
}


void pipeline::

set_link(std::string const& program_name , std::string const& uniform_name)
{
  program_iterator p_it(find_program(program_name));

  if(p_it != programs_.end())
  {
    if(uniforms_.aviable(uniform_name))
    {
      if(p_it->id() != 0)
      {
        links_.push_back(uniform_link(p_it->id(),uniform_name));
      }

      else
      {
        std::cerr << std::endl
                  << "program [" << program_name << "] isn't linked"
                  << std::endl;
      }
    }

    else
    {
      std::cerr << std::endl
                << "uniform [" << uniform_name << "] doesn't exist"
                << std::endl;
    }
  }

  else
  {
    std::cerr << std::endl
              << "program [" << program_name << "] doesn't exist"
              << std::endl;
  }
}


void pipeline::

link_programs()
{
  for(auto p_it(programs_.begin()) ; p_it != programs_.end() ; ++p_it)
  {
    p_it->link();
  }
}


program_iterator const pipeline::

find_program(std::string const& name)
{
  program_iterator p_it;

  for(p_it = programs_.begin() ; p_it != programs_.end() ; ++p_it)
  {
    if(p_it->equal(name)) break;
  }

  return p_it;
}


stage_iterator const pipeline::

find_stage(std::string const& path)
{
  stage_iterator s_it;

  for(s_it = stages_.begin() ; s_it != stages_.end() ; ++s_it)
  {
    if(s_it->get()->equal(path)) break;
  }

  return s_it;
}
