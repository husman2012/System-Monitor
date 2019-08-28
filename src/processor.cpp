#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <numeric>
#include <string>
#include <iostream>
#include <unistd.h>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  vector<string> prev_cpu_util =  LinuxParser::CpuUtilization(LinuxParser::kStatFilename);
  usleep(100000);
  vector<string> curr_cpu_util = LinuxParser::CpuUtilization(LinuxParser::kStatFilename);
  
  vector<float> prev_util = String_To_Float(prev_cpu_util);
  vector<float> curr_util = String_To_Float(curr_cpu_util);
  
  
  vector<float> Prev = Calc_Utilization(prev_util);
  vector<float> Curr = Calc_Utilization(curr_util);
  
  float total =  Curr[0] - Prev[0];
  float idle = Curr[1] - Prev[1];
  double cpu_total = (total - idle) / total;
  std::cout << cpu_total;
  
  return cpu_total;
}

vector<float> Processor::Calc_Utilization(std::vector<float> test){
  
  float user_time = test[0];
  float nice_time = test[1];
  float system_time = test[2];
  float idle_time = test[3];
  float iowait = test[4];
  float irq = test[5];
  float softirq = test[6];
  float steal = test[7];
  float guest = test[8];
  float guest_nice = test[9];
  
  user_time = user_time - guest;
  nice_time = nice_time - guest_nice;
  float idle_all_time = idle_time + iowait;
  float system_all_time = system_time + irq + softirq;
  
  float idle = idle_all_time + iowait;
  float non_idle = user_time + nice_time + system_all_time + irq + softirq + steal;
  float total = idle + non_idle;
  
  vector<float> values_array = {total, idle};
  return values_array;
}
    
vector<float> Processor::String_To_Float(std::vector<string> util){
  std::vector<float> util_f = {};
  
  for (unsigned i=0; i < util.size(); i++){
    std::string elem = util[i]; 
    util_f.push_back(std::stof(elem));
  }
  return util_f;
}