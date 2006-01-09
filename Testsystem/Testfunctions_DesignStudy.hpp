// Oliver Kullmann, 8.1.2006 (Swansea)

#ifndef TESTFUNCTIONS_UJJhhgFR45

#define TESTFUNCTIONS_UJJhhgFR45

#include <exception>

#include "TestBaseClass_DesignStudy.hpp"
#include "TestExceptions_DesignStudy.hpp"

namespace OKlib {

  namespace TestSystem {

    class Test1 : public OKlib::TestSystem::TestBase<Test1> {
      typedef Test1 test_type;
      void test(OKlib::TestSystem::Basic, std::ostream& log) {
        log << "Test: OKlib::TestSystem::Test1, Basic\n";
        typedef OKlib::TestSystem::Basic level_type;
        //throw std::runtime_error("In OKlib::TestSystem::Test1::test");
        //OKLIB_THROW("IN TEST1");
        throw 5;
      }
    };

    
  }

}

#endif
