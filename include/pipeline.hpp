#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <program.hpp>
#include <uniform_map.hpp>

#include <vector>


typedef std::vector<program>::iterator program_iterator;

typedef std::vector<std::shared_ptr<stage> >::iterator stage_iterator;


class pipeline
{
  public :

  void enable(std::string const&);

  void add_program(std::string const&);

  void set_stage(std::string const&,std::string const&);

  void set_link(std::string const&,std::string const&);

  void link_programs();


  uniform_map uniforms_;


  private :

  program_iterator const find_program(std::string const&);

  stage_iterator const find_stage(std::string const&);


  std::vector<program> programs_;

  std::vector<std::shared_ptr<stage> > stages_;

  std::vector<uniform_link> links_;
};

#endif
