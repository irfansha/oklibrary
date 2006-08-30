// Oliver Kullmann, 22.8.2006 (Swansea)

/*!
  \file TestSystem/plans/TestBaseClass.hpp
  \brief Plans for the module with the (user) base of the test hierarchy

  \todo Messages:
  Use Messages for all output.
  \todo Log-Messages:
  Replace TestBase::log_message in all tests by TestBase::log (potentially
  updating TestBase::log), and then remove TestBase::log_message.
  \todo Testing:
  Try to extend the level hierarchy (whether it "works").
  \todo Unknown exceptions:
  In case an unknown exception is thrown, there should be a global option to
  let this exception through (perhaps kind of a "handler").
  \todo Transition:
  Once the transition is done, rename "TestBaseClass_DesignStudy.hpp" to
  "TestBaseClass.hpp", and check the doxygen-documentation (which yet doesn't work due
  to multiple definitions of the same entities).
  

*/

