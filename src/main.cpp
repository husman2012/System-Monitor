#include "ncurses_display.h"
#include "system.h"
#include <iostream>
#include "linux_parser.h"

int main() {
  System system;
  std::cout<<system.Processes()[0].User();
  //NCursesDisplay::Display(system);
}