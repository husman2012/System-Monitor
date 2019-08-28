#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>
#include "linux_parser.h"
#include <algorithm>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization(string directory) {
  string line;
  vector<float> mem;
  std::ifstream stream(kProcDirectory + directory);
  int i = 0;
  while (stream.is_open() && i < 2){
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream.good() && i < 2) {
      string data;
      linestream >> data;
      if (isdigit(data[0])){
        mem.push_back(std::stof(data));
        i++;
      }
      
    }
  }
  float memTotal = mem[0];
  float memFree = mem[1];
  float Total_used = memTotal - memFree;
  return Total_used/memTotal;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime(string directory) { 
  long up_time, idle_time;
  string line;
  std::ifstream stream(kProcDirectory + directory);
  if (stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> up_time >> idle_time;
  }
  return up_time;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization(string directory) {
  string line;
  vector<string> cpu_test;
  std::ifstream stream(kProcDirectory + directory);
  if (stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    int i = 0;
    while (linestream.good() && i < 10) {
      string data;
      linestream >> data;
      if (isdigit(data[0])){
        cpu_test.push_back(data);
      }
      i++;
    }
  }
  return cpu_test;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses(string directory) {
  string line;
  string data;
  std::ifstream stream(kProcDirectory + directory);
  while (stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> data;
    if (data == "processes"){
      linestream >> data;
      return std::stoi(data);
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses(string directory) {
  string line;
  string data;
  std::ifstream stream(kProcDirectory + directory);
  while (stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> data;
    if (data == "procs_running"){
      linestream >> data;
      return std::stoi(data);
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string directory = std::to_string(pid) + kCmdlineFilename;
  string line;
  std::ifstream stream(kProcDirectory + directory);
  if (stream.is_open()){
    std::getline(stream,line);
    return line;
  }
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string directory = std::to_string(pid) + kStatusFilename;
  string line;
  std::ifstream stream(kProcDirectory + directory);
  int i = 0;
  string data;
  while(stream.is_open() && i < 18){
    std::getline(stream,line);
    if (i == 17){
      std::istringstream linestream(line);
      linestream >> data;
      linestream >> data;
    }
    i++;
  }
  return data;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string directory = std::to_string(pid) + kStatusFilename;
  string line;
  std::ifstream stream(kProcDirectory + directory);
  int i = 0;
  string data;
  while(stream.is_open() && i < 9){
    std::getline(stream,line);
    if (i == 8){
      std::istringstream linestream(line);
      linestream >> data;
      linestream >> data;
    }
    i++;
  }
  return data;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string uid = LinuxParser::Uid(pid);
  string line;
  std:: ifstream stream(kPasswordPath);
  int i = 0;
  char delimiter = ':';
  string data;
  
  while(stream.is_open() && i < 50){
    std::getline(stream,line);
    vector<string> line_array = {};
    char char_array[100];
    for (unsigned int i = 0 ; i < line.size(); i++){
      if(line[i] == delimiter){
        std::string p = char_array;
        std::cout << p << "\n";
        if (p == uid){
          return line_array[0];
        }
        line_array.push_back(p);
      }
      char_array[i] = line[i];     
    }
    i++;
  }
  
  return "0";
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }