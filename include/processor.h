#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include <string>
using std::string;
using std::vector;


class Processor {
 public:
  
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  vector<string> cpu_util;
  vector<float> Calc_Utilization(std::vector<float> test);
  vector<float> String_To_Float(std::vector<string> util);
};

#endif