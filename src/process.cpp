#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "system.h"
#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  string directory = std::to_string(pid_);
  vector<float> cpu_utils = Parse_CPU_Util(directory);
  float util = Calc_Utilization(cpu_utils);
  cpu_util = util;
  return util;
}


// TODO: Return the command that generated this process
string Process::Command() {
  return LinuxParser::Command(pid_);
}

// TODO: Return this process's memory utilization
string Process::Ram() {
  string ram_s = LinuxParser::Ram(pid_);
  int ram_i = std::stof(ram_s);
  ram_i = ram_i / 1024;
  ram_s = std::to_string(ram_i);
  return ram_s; }

// TODO: Return the user (name) that generated this process
string Process::User() {
  string user = LinuxParser::User(pid_);
  return user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
  string pid = std::to_string(pid_);
  vector<float> time_array = Parse_CPU_Util(pid);
  
  float starttime = time_array[4];
  auto Hertz = sysconf(_SC_CLK_TCK);
  long int time_s = starttime/Hertz;
  long int sys_time = System::UpTime();
  long int up_time = sys_time - time_s;
  return up_time;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return cpu_util > a.cpu_util;
  }

void Process::Pid(int pid){
  pid_ = pid;
}

vector<float> Process::Parse_CPU_Util(string directory){
  string line;
  vector<string> cpu_test;
  std::ifstream stream(LinuxParser::kProcDirectory + directory + "/stat");
  if (stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    int i = 0;
    while (linestream.good() && i < 30) {
      string data;
      linestream >> data;
      cpu_test.push_back(data);
      i++;
    }
  }
  vector<string> cpu_utils = {cpu_test[13], cpu_test[14], cpu_test[15], cpu_test[16], cpu_test[21]};
 
  vector<float> cpu_utils_f = String_To_Float(cpu_utils);
  return cpu_utils_f;
}

float Process::Calc_Utilization(std::vector<float> test){
  
  float utime = test[0];
  float stime = test[1];
  float cutime = test[2];
  float cstime = test[3];
  float starttime = test[4];
  auto Hertz = sysconf(_SC_CLK_TCK);
  
  float total_time = utime + stime + cutime + cstime;
  long int uptime = LinuxParser::UpTime(LinuxParser::kUptimeFilename);
  
  float seconds = uptime - (starttime / Hertz);
  float cpu_usage = ((total_time / Hertz) / seconds);
  return cpu_usage;
}
    
vector<float> Process::String_To_Float(std::vector<string> util){
  std::vector<float> util_f = {};
  
  for (unsigned i=0; i < util.size(); i++){
    std::string elem = util[i]; 
    util_f.push_back(std::stof(elem));
  }
  return util_f;
}