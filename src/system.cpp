#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() {
  cpu_.Utilization();
  return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  vector<int> pids = LinuxParser::Pids();
  Process *processes = new Process[pids.size()];
  for (unsigned int id = 0; id < pids.size(); id++){
    processes[id].Pid(pids[id]);
    processes_.push_back(processes[id]);
  }
  return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {
  return LinuxParser::MemoryUtilization(LinuxParser::kMeminfoFilename); 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(LinuxParser::kStatFilename); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(LinuxParser::kStatFilename); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(LinuxParser::kUptimeFilename); }