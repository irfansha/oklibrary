#include <iostream>

#include "TestBaseClass.hpp"

#include "Enumeration_Testobjects.hpp"

int main() {
  return OKlib::TestSystem::TestBase::run_tests_default(std::cerr);
} 
