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

const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};


vector<string> CpuUtilization() {
    vector <string> cpu_times;
    string line;
    string cpu = "cpu";
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()){
        while(std::getline(stream, line) && line != "intr"){
            std::cout << line;
        }

    }

}

int main(){
    CpuUtilization();
    
}