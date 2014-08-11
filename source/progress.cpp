#include <progress.hpp>

progress::progress(std::string text,unsigned long total)
:text_(text),total_(total),last_(0),current_percent_(0){}

void progress::update(unsigned long current) {
   current_percent_ = (100*current)/total_;
   if(((100*current)/total_) != last_) {
      std::cout<<"\r";
      std::cout<<text_+"..."+std::to_string(current_percent_)+"%";
      last_ = current_percent_;
   }
}

void progress::finalize() {
      std::cout<<"\r";
      std::cout<<text_+"...DONE"<<std::endl;
}
