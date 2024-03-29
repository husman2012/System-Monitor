#ifndef PROCESS_H
#define PROCESS_H

#include "linux_parser.h"
#include <string>
#include <vector>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(){};
  Process(int pid): pid_(pid){};
  void Pid(int pid);
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
   float cpu_util;
   int pid_;
   std::vector<float> Parse_CPU_Util(std::string directory);
   float Calc_Utilization(std::vector<float> test);
   std::vector<float> String_To_Float(std::vector<std::string> util);

};

#endif