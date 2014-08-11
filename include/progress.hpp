#ifndef PROGRESS
#define PROGRESS

#include <iostream>
#include <string>

class progress {

   public:

   progress(std::string,unsigned long);
   void update(unsigned long);
   void finalize();

   private:

   std::string text_;
   unsigned long total_;
   unsigned int last_;
   unsigned int current_percent_;

};

#endif
